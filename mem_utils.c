// Graham Arnold
// Pierre Laury
// CSE 374 HW6
// 5/18/17
// This auxlilary program contains the
// implementation of check heap
// and any helper functions needed
// these functions check the status of the free list
// to ensure there are no errors with the memory system

#include "mem_impl.h"

memBlock* freeList;
uintptr_t minSize;


// checks  if blocks
// are ordered in stricly
// increasing memory addresses
// Accepts a single argument memBlock pointer
void check_ordering(memBlock* temp) {
    uintptr_t address = (uintptr_t)temp + temp->size + sizeof(memBlock);
    assert(address < (uintptr_t)temp->nextBlock);
}

// checks to make sure
// block sizes are positive
// and larger than minimum size
// Accepts a single argument memBlock pointer
void check_size(memBlock* temp) {
    fprintf(stdout, "size: %lu\n", (uintptr_t)temp->size);
    assert((uintptr_t)temp->size > 0);
    assert(temp->size >= minSize);
}

// checks blocks length
// to ensure it doesnt
// overlap with another existing
// block of memory
// Accepts a single argument memBlock pointer
void check_overlap(memBlock* temp) {
    assert(temp < temp->nextBlock);
}

// Checks the free list for errors in the memory system
void check_heap() {
  memBlock* temp = freeList->nextBlock;
  while (temp != NULL && temp->nextBlock != NULL) {
    check_overlap(temp);
    check_size(temp);
    check_ordering(temp);
    temp = temp->nextBlock;
  }
}
