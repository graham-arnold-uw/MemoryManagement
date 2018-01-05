// Graham Arnold
// Pierre Laury
// CSE 374 HW6
// 5/18/17
// Header file for memory management package

#ifndef MEM_H
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <string.h>
#include <ctype.h>

// receives a size parameter
// for how many bytes of memory
// should be allocated by the function
void* getmem(uintptr_t size);

// frees blocks of storage at location p. Accepts a single argument: a pointer
// p pointing to a block of storage to free.
void freemem(void* p);

// stores statistics about the current state of the memory manager in the three
// integer variables total_size, total_free and n_free_blocks. Accepts three
// arguments: uintptr pointers to integers representing stats about the memory
// manager.
void get_mem_stats(uintptr_t* total_size, uintptr_t*
                   total_free, uintptr_t* n_free_blocks);

// receives a pointer to a file as a paramter
// writes into the given file the current address and size of each block of
// unallocated memory in the free list
// includes error checking if file is null
void print_heap(FILE* f);

#endif
