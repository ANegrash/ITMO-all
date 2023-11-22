#include "mem.h"
#include "mem_internals.h"
#include <stdio.h>
#include "util.h"


void debug(const char* fmt, ... );
static struct block_header* get_header_block(void *mem){
    return (struct block_header*)((uint8_t*) mem - offsetof(struct block_header, contents));
}

void test_1(void const* heap) {
    debug("Test 1. Memory allocation\n");
    void* mem = _malloc(256);
    if(mem == NULL) {
        err("Error. Not allocated\n");
    }

    struct block_header* block_header = get_header_block(mem);
    if (block_header->capacity.bytes != 256) {
        err("Error. Wrong size\n");
    }
    if (block_header->is_free) {
        err("Error. Block is free, must be unfree\n");
    }
    debug("Memory allocation\n");
    debug_heap(stdout, heap);

    _free(mem);
    debug("Memory free\n");
    debug_heap(stdout, heap);
    debug("Test 1. End\n");
}

void test_2(void const* heap) {
    debug("Test 2. Free one block from 3\n");
    void* mem_1 = _malloc(666);
    void* mem_2 = _malloc(1024);
    void* mem_3= _malloc(1024);
    if(mem_1 == NULL || mem_2 == NULL || mem_3 == NULL ) {
        err("Error. Memory doesn't allocated\n");
    }
    debug("Memory allocated\n");
    debug_heap(stdout, heap);

    _free(mem_2);
    debug("Free second block\n");
    debug_heap(stdout, heap);

    if (get_header_block(mem_1)->is_free) {
        err("Error. Free wrong block - 1\n");
    }
    if (!get_header_block(mem_2)->is_free) {
        err("Error. Right block didn't free\n");
    }
    if (get_header_block(mem_3)->is_free) {
        err("Error. Free wrong block - 3\n");
    }
    _free(mem_1);
    _free(mem_3);
    debug("Test 2. End\n");
}

void test_3(void const* heap) {
    debug("Test 3. Free 2 blocks from 4\n");
    void* mem_1 = _malloc(666);
    void* mem_2 = _malloc(1024);
    void* mem_3= _malloc(1024);
    void* mem_4= _malloc(70);
    if(mem_1 == NULL || mem_2 == NULL || mem_3 == NULL || mem_4 == NULL) {
        err("Error. Memory didn't allocated\n");
    }
    debug("Memory allocated\n");
    debug_heap(stdout, heap);

    _free(mem_2);
    _free(mem_4);
    debug("Free 2 and 4 blocks\n");
    debug_heap(stdout, heap);

    if (get_header_block(mem_1)->is_free) {
        err("Error. 1 free\n");
    }
    if (!get_header_block(mem_2)->is_free) {
        err("Error. 2 unfree\n");
    }
    if (get_header_block(mem_3)->is_free) {
        err("Error. 3 free\n");
    }
    if (!get_header_block(mem_4)->is_free) {
        err("Error. 4 unfree\n");
    }

    _free(mem_1);
    _free(mem_3);
    debug("Test 3. End\n");
}

void test_4(void const* heap) {
    debug("Test 4. Without enough memory new region allocated\n");
    void* mem_1 = _malloc(1024);
    void* mem_2= _malloc(1024);
    void* mem_3= _malloc(10000);

    debug("Memory allocated\n");
    debug_heap(stdout, heap);
    if(mem_1 == NULL || mem_2 == NULL || mem_3 == NULL) {
        err("Error. didn't allocated all\n");
    }
    debug("Test 4. End\n");
}

void test_5(void const* heap) {
    debug("Test 5. Without memory, allocation new region can't be at next addresses, need to be done at another\n");
    void* mem_1= _malloc(9000);

    debug("Memory allocation\n");
    debug_heap(stdout, heap);
    if(mem_1 == NULL) {
        err("Error. Memory didn't allocated - fir\n");
    }

    struct block_header* block_header_1 = get_header_block(mem_1);
    while(block_header_1->next !=NULL) {
        block_header_1 = block_header_1->next;
    }

    void* map_addr = mmap((void*)(block_header_1->contents + block_header_1->capacity.bytes), 10000, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);
    if( map_addr == NULL ||  map_addr == MAP_FAILED) {
        err("Error. Memory didn't allocated - sec\n");
    }

    void* mem_2 = _malloc(1024);
    debug("Memory allocation\n");
    debug_heap(stdout, heap);

    struct block_header* block_header_2 = get_header_block(mem_2);
    if((void*)(block_header_1->contents + block_header_1->capacity.bytes) == (void*)block_header_2) {
        err("Error. Memory allocated to close\n");
    }

    _free(mem_1);
    _free(mem_2);
    debug("Test 5. End\n");
}
