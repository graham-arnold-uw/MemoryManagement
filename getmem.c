// Graham Arnold
// Pierre Laury
// CSE 374 HW6
// 5/18/17
// Program file for getmem function
// which returns pointer to new block of memory storage

#include <inttypes.h>
#include <stdlib.h>
#include "mem_impl.h"
#include "mem.h"

#define ALLOCATESIZE  8000
#define MINBLOCKSIZE  64

// helper function prototype
void addMem(uintptr_t size);

uintptr_t totalSystMem;
uintptr_t minSize = MINBLOCKSIZE;
memBlock * freeList;
// receives a size parameter
// for how many bytes of memory
// should be allocated by the function
void* getmem(uintptr_t size) {
    if (size <= 0) {
        return NULL;
    }
    // if freelist is empty create new empty freeList node
    if (freeList == NULL) {
        totalSystMem = 0;
        freeList = (memBlock *)malloc(sizeof(memBlock));
        freeList->nextBlock = NULL;
        freeList->size = 0;
    }
    check_heap();
    uintptr_t alignedSize;
    int excessSize = size % 16;
    // round requested size to nearest 16
    // or if smaller than min size
    // set it to that
    if (size < MINBLOCKSIZE) {
        alignedSize = MINBLOCKSIZE;
    } else if (excessSize != 0) {
        alignedSize = size + 16 - excessSize;
    }  else {
        alignedSize = size;
    }
    // check for a large enough block
    // on the freelist
    memBlock* currBlock = freeList;
    int blockFound = 0;
    while (currBlock->nextBlock != NULL) {
        if (currBlock->nextBlock->size >= alignedSize) {
            currBlock = currBlock->nextBlock + 1;
            blockFound = 1;
            break;
        } else {
            currBlock = currBlock->nextBlock;
        }
    }
    // if no block on the free list
    // is big enough, need to grab
    // more memory from malloc
    if (!blockFound) {
        if (alignedSize > ALLOCATESIZE) {
            addMem(alignedSize);
        } else {
            addMem(ALLOCATESIZE);
        }
    }
    check_heap();
    // loop through free list again looking for a big
    // enough block, split the block if its big enough
    currBlock = freeList;
    while (currBlock->nextBlock != NULL) {
        // looks for a big enough block
        if (currBlock->nextBlock->size >= alignedSize) {
            // if the next block is bigger than necessary
            // split it and return just a chunk
            if (currBlock->nextBlock->size - alignedSize > MINBLOCKSIZE) {
                currBlock = currBlock->nextBlock;
                memBlock*  splitBlock = (memBlock *)((uintptr_t)currBlock
                + currBlock->size - alignedSize) + 1;
                splitBlock->size = alignedSize;
                splitBlock->nextBlock = NULL;
                currBlock->size = currBlock->size - alignedSize;
                check_heap();
                return splitBlock;
            } else {
                // if the next block is correctly sized
                // reorder list to remove it
                // and return that block
                memBlock* targetBlock = currBlock->nextBlock + 1;
                currBlock->nextBlock = currBlock->nextBlock->nextBlock;
                check_heap();
                return targetBlock;
            }
        } else {
            currBlock = currBlock->nextBlock;
        }
    }
    check_heap();
    return NULL;
}

void addMem(uintptr_t size) {
    // create new block of memory
    // with correct size
    memBlock* newBlock = (memBlock*)malloc(size+sizeof(memBlock));
    totalSystMem += size+sizeof(memBlock);
    newBlock->size = size;
    newBlock->nextBlock = NULL;
    // now find its correct place in the free list
    // sorted according to increasing address
    memBlock* currBlock = freeList;
    while (currBlock->nextBlock != NULL) {
        if ((uintptr_t)(currBlock->nextBlock) > (uintptr_t) newBlock) {
            newBlock->nextBlock = currBlock->nextBlock;
            currBlock->nextBlock = newBlock;
            return;
        } else {
            currBlock = currBlock->nextBlock;
        }
    }
    // if it reaches here then the newBlock belongs
    // at the end of the free list
    currBlock->nextBlock = newBlock;
    return;
}
