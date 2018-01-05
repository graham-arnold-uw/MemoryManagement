// Graham Arnold
// Pierre Laury
// CSE 374 HW6
// 5/18/17
// print_heap.c prints out the currently available memory blocks
// on the free list which keeps track of the memory management

# include "mem_impl.h"

// takes FILE f as parameter
// writes the address and size of each block in free_list into the given file
// if free_list or the file is null, it will print the corresponding error
// messages
memBlock* freeList;

// receives a pointer to a file as a paramter
// writes into the given file the current address and size of each block of
// unallocated memory in the free list
// includes error checking if file is null
void print_heap(FILE * f) {
    if (f == NULL) {
        perror("Error: output file not received\n");
        return;
    } else if (freeList == NULL) {
        perror("Error: heap is NULL\n");
        return;
    }
    if (freeList->nextBlock != NULL) {
        memBlock* temp = freeList->nextBlock;
        while (temp != NULL) {
            fprintf(f, "address: %p size: %d \n", temp, (int)temp->size);
            temp = temp->nextBlock;
        }
    }
}
