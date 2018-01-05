// Graham Arnold
// Pierre Laury
// CSE 374 HW6
// 5/18/17
// get_mem_stats.c stores statistics about the current state of the memory
// manager

#include "mem_impl.h"

memBlock* freeList;
uintptr_t totalSystMem;

// stores statistics about the current state of the memory manager in the three
// integer variables total_size, total_free and n_free_blocks. Accepts three
// arguments: uintptr pointers to integers representing stats about the memory
// manager.
void get_mem_stats(uintptr_t* total_size, uintptr_t* total_free,
    uintptr_t* n_free_blocks) {
    if (freeList == NULL) {
        *total_size = 0;
        *total_free = 0;
        *n_free_blocks = 0;
    } else if (freeList != NULL) {
        uintptr_t freeMemBlock = 0;
        uintptr_t freeMem = 0;
        *total_size = totalSystMem;
        if (freeList->nextBlock != NULL) {
            memBlock* next = freeList;
            while (next->nextBlock != NULL) {
                freeMemBlock++;
                next = next->nextBlock;
                freeMem = freeMem + next->size + sizeof(memBlock);
            }
        }
        *n_free_blocks = freeMemBlock;
        *total_free = freeMem;
    }
}
