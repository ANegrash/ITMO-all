#include "mem.h"
#include "mem_internals.h"
#include <stddef.h>
#include <unistd.h>
#include "util.h"

void debug_block(struct block_header *b, const char *fmt, ...);

void debug(const char *fmt, ...);

extern inline block_size size_from_capacity(block_capacity cap);

extern inline block_capacity capacity_from_size(block_size sz);

static bool block_is_big_enough(size_t query, struct block_header *block) { return block->capacity.bytes >= query; }

static size_t pages_count(size_t mem) { return mem / getpagesize() + ((mem % getpagesize()) > 0); }

static size_t round_pages(size_t mem) { return getpagesize() * pages_count(mem); }

static void block_init(void *restrict addr, block_size block_sz, void *restrict next) {
    *((struct block_header *) addr) = (struct block_header) {
            .next = next,
            .capacity = capacity_from_size(block_sz),
            .is_free = true
    };
}

static size_t region_actual_size(size_t query) { return size_max(round_pages(query), REGION_MIN_SIZE); }

extern inline bool region_is_invalid(const struct region *r);


static void *map_pages(void const *addr, size_t length, int additional_flags) {
    return mmap((void *) addr, length, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS | additional_flags, 0, 0);
}

/*  аллоцировать регион памяти и инициализировать его блоком */
static struct region alloc_region(void const *addr, size_t query) {
    size_t offset = region_actual_size(query);
    void *allocated = map_pages(addr, offset, MAP_FIXED_NOREPLACE);
    if (allocated == MAP_FAILED) {
        allocated = map_pages(addr, query, 0);
        if (allocated == MAP_FAILED) {
            return REGION_INVALID;
        }
    }
    struct region memory_region = (struct region) {.addr=allocated, .size=query, .extends=false};
    block_size bs = (block_size) {.bytes=query};
    block_init(allocated, bs, NULL);
    return memory_region;
}

static void *block_after(struct block_header const *block);

void *heap_init(size_t initial) {
    const struct region region = alloc_region(HEAP_START, initial);
    if (region_is_invalid(&region)) return NULL;
    return region.addr;
}

#define BLOCK_MIN_CAPACITY 24

/*  --- Разделение блоков (если найденный свободный блок слишком большой )--- */

static bool block_splittable(struct block_header *restrict block, size_t query) {
    bool have_enough_space = query + offsetof(struct block_header, contents) + BLOCK_MIN_CAPACITY <= block->capacity.bytes;
    return block->is_free && have_enough_space;
}

static bool split_if_too_big(struct block_header *block, size_t query) {
    bool is_splittable = block_splittable(block, query);
    if (is_splittable) {
        void *new_block = (struct block_header *) (block->contents + query);
        block_init((void *) new_block, (block_size) {block->capacity.bytes - query}, NULL);
        block->capacity.bytes = query;
        block->next = new_block;
        return true;
    }
    return false;
}


/*  --- Слияние соседних свободных блоков --- */

static void *block_after(struct block_header const *block) {
    return (void *) (block->contents + block->capacity.bytes);
}

static bool blocks_continuous(
        struct block_header const *fst,
        struct block_header const *snd) {
    return (void *) snd == block_after(fst);
}

static bool mergeable(struct block_header const *restrict fst, struct block_header const *restrict snd) {
    return fst->is_free && snd->is_free && blocks_continuous(fst, snd);
}

static bool try_merge_with_next(struct block_header *block) {
    struct block_header *next_block = block->next;
    if (next_block == NULL || !mergeable(block, next_block)) {
        return false;
    } else {
        block->next = next_block->next;
        block->capacity.bytes += size_from_capacity(next_block->capacity).bytes;
        return true;
    }
}


/*  --- ... ecли размера кучи хватает --- */

struct block_search_result {
    enum {
        BSR_FOUND_GOOD_BLOCK, BSR_REACHED_END_NOT_FOUND, BSR_CORRUPTED
    } type;
    struct block_header *block;
};


static struct block_search_result find_good_or_last(struct block_header *restrict block, size_t sz) {
    struct block_header *current_block = block;
    struct block_header *last_block = block;
    while (current_block) {
        while (current_block->is_free &&
               (block_is_big_enough(sz, current_block) || try_merge_with_next(current_block))) {
            if (block_is_big_enough(sz, current_block)) {
                return (struct block_search_result) {.type = BSR_FOUND_GOOD_BLOCK, .block = current_block};
            }
        }
        last_block = current_block;
        current_block = current_block->next;
    }
    return (struct block_search_result) {.type = BSR_REACHED_END_NOT_FOUND, .block = last_block};
}

/*  Попробовать выделить память в куче начиная с блока `block` не пытаясь расширить кучу
 Можно переиспользовать как только кучу расширили. */
static struct block_search_result try_memalloc_existing(size_t query, struct block_header *block) {
    struct block_search_result res = find_good_or_last(block, query);
    if (res.type == BSR_FOUND_GOOD_BLOCK) {
        split_if_too_big(res.block, query);
        res.block->is_free = false;
    }
    return res;

}


static struct block_header *grow_heap(struct block_header *restrict last, size_t query) {
    struct region region = alloc_region(last->contents + last->capacity.bytes, query);
    struct block_header *block = region.addr;
    last->next = block;
    bool b = try_merge_with_next(last);
    if (b) {
        return last;
    } else {
        return block;
    }
}

/*  Реализует основную логику malloc и возвращает заголовок выделенного блока */
static struct block_header *memalloc(size_t query, struct block_header *heap_start) {
    query = size_max(query, BLOCK_MIN_CAPACITY);
    struct block_search_result result = try_memalloc_existing(query, heap_start);
    switch (result.type) {
        case BSR_CORRUPTED:{
            return NULL;
        }
        case BSR_REACHED_END_NOT_FOUND:{
            result.block = grow_heap(result.block, query);
            split_if_too_big(result.block, query);
            break;
        }
        default:{
            break;
        }
    }
    result.block->is_free = false;
    return result.block;
}

void *_malloc(size_t query) {
    struct block_header *const addr = memalloc(query, (struct block_header *) HEAP_START);
    if (addr) return addr->contents;
    else return NULL;
}

static struct block_header *block_get_header(void *contents) {
    return (struct block_header *) (((uint8_t *) contents) - offsetof(struct block_header, contents));
}

void _free(void *mem) {
    if (!mem) return;
    struct block_header *header = block_get_header(mem);
    header->is_free = true;
    while (try_merge_with_next(header));
}
