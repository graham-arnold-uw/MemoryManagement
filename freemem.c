// Graham Arnold
// Pierre Laury
// CSE 374 HW6
// 5/18/17
// freemem.c frees blocks of storage at a certain location to the pool of
// available free storage.

#include "mem_impl.h"

memBlock* addBlock(void* p, memBlock* addBlock);
void combineBlocks(memBlock* currentBlock);

// frees blocks of storage at location p. Accepts a single argument: a pointer
// p pointing to a block of storage to free.
void freemem(void* p) {
    if (p != NULL) {
        check_heap();
        freeList = addBlock(p, freeList);
    } else {
        perror("Error: Cannot free given block.\n");
    }
    check_heap();
}

// adds a new block to the free list. Accepts two arguments: a pointer to the
// block to free and a pointer to the current block in the list
memBlock* addBlock(void* p, memBlock* currentBlock) {
    if (currentBlock != NULL && (memBlock*)p >= currentBlock) {
        currentBlock->nextBlock = addBlock(p, currentBlock->nextBlock);
    } else {
        memBlock* temp = currentBlock;
        currentBlock = (memBlock*)p;
        if (currentBlock == NULL) {
            currentBlock->nextBlock = NULL;
        } else {
            currentBlock->nextBlock = temp;
        }
    }
    combineBlocks(currentBlock);
    return currentBlock;
}

// checks whether the block to be removed is located adjacent to one or more
// free blocks and combines them if that is the case.
void combineBlocks(memBlock* currentBlock) {
    if (currentBlock->nextBlock != NULL) {
        uintptr_t addressLocation = (uintptr_t) currentBlock;
        memBlock* newAddress = (memBlock*) (addressLocation + sizeof(memBlock)
        + currentBlock->size);
        if (newAddress == currentBlock->nextBlock) {
            currentBlock->size = currentBlock->size
            + currentBlock->nextBlock->size + sizeof(memBlock);
            currentBlock->nextBlock = currentBlock->nextBlock->nextBlock;
        }
    } else {
        return;
    }
}
