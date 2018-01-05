// Graham Arnold
// Pierre Laury
// CSE 374 HW6
// 5/18/17
// header file mem_impl.h declares free list data structure and check_heap
// function. Not part of public interface.


#ifndef MEM_IMPL_H
#define MEM_IMPL_H

#include "mem.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <inttypes.h>
#include <assert.h>

// memBlock struct definition
typedef struct memBlock {
  uintptr_t size;
  struct memBlock* nextBlock;
}memBlock;

// free list data structure declaration.
extern memBlock* freeList;
uintptr_t blockSize;

// Checks the free list for errors in the memory system
void check_heap();

extern uintptr_t minSize;
extern uintptr_t totalSystMem;

#endif
