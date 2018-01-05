# Graham Arnold
# Pierre Laury
# CSE 374 HW6
# 5/18/17
# Makefile file to compile all files required to build the the test program

all: bench

bench: bench.o print_heap.o get_mem_stats.o freemem.o getmem.o mem_utils.o
	gcc -Wall -g -o bench bench.o print_heap.o get_mem_stats.o freemem.o getmem.o mem_utils.o

bench.o: mem.h bench.c
	gcc -Wall -std=c11 -g -c bench.c

print_heap.o: mem.h mem_impl.h print_heap.c
	gcc -Wall -std=c11 -g -c print_heap.c

get_mem_stats.o: mem.h mem_impl.h get_mem_stats.c
	gcc -Wall -std=c11 -g -c get_mem_stats.c

freemem.o: mem.h mem_impl.h freemem.c
	gcc -Wall -std=c11 -g -c freemem.c

getmem.o: mem.h mem_impl.h getmem.c
	gcc -Wall -std=c11 -g -c getmem.c

mem_utils.o: mem.h mem_impl.h mem_utils.c
	gcc -Wall -std=c11 -g -c mem_utils.c

#tests bench.c with default values
test: bench
	./bench

clean:
	rm -f *.o bench *~
