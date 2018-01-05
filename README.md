Final Assigment for EE374 Programming Concepts and Tools

The assignment goal was to Implement and test a memory management 
package that has the same functionality as the standard library malloc and free functions

Description of files:

mem.h - header file containing declarations of the public functions in 
the memory manager (including appropriate comments). This is the interface 
that clients of the getmem/freemem package use.

getmem.c - implementation of function getmem.

freemem.c - implementation of function freemem.

get_mem_stats.c - implementation of function get_mem_stats.

print_heap.c - implementation of function print_heap.

mem_utils.c - implementation of function check_heap. 

mem_impl.h - header file with declarations of internal implementation details shared by more than one 
of the above files. 
