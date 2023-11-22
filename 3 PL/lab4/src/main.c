#include "test.h"
#include "mem.h"
#include "mem_internals.h"
#include <stdio.h>
#include "util.h"

void debug(const char* fmt, ... );

int main() {
    void* heap = heap_init(10000);
    if(heap == NULL) {
        err("Heap uninit");
    }
    debug("Heap init\n");
    debug_heap(stdout, heap);
    test_1(heap);
    test_2(heap);
    test_3(heap);
    test_4(heap);
    test_5(heap);
    return 0;
}
