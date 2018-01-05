// Graham Arnold
// Pierre Laury
// CSE 374 HW6
// 5/18/17
// This testing program validates the
// getmem and freemem programs
// by allocating and deallocating memory
// and checking the results

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <inttypes.h>
#include "mem.h"


int main(int argc, char** argv) {
    int ntrials = 10000;
    int pctget = 50;
    int pctlarge = 10;
    int small_limit = 200;
    int large_limit = 20000;
    int random_seed = time(NULL);

    if (argc > 7) {
        perror("Error: this program only accepts up to 6 arguments\n");
        return 1;
    }

    if (argc > 1) {
        ntrials = atoi(argv[1]);
    }
    if (argc > 2) {
        pctget = atoi(argv[2]);
    }
    if (argc > 3) {
        pctlarge = atoi(argv[3]);
    }
    if (argc > 4) {
        small_limit = atoi(argv[4]);
    }
    if (argc > 5) {
        large_limit = atoi(argv[5]);
    }
    if (argc > 6) {
        random_seed = atoi(argv[6]);
    }

    srand(random_seed);

    void ** allocatedBlocks = (void**)malloc(ntrials*sizeof(void*));
    int index = 0;
    uintptr_t freeBlocks;
    uintptr_t totalAlloc;
    uintptr_t totalFree;
    uintptr_t inputSize;
    clock_t begin = clock();
    double totalRunTime;
    for (int i = 0; i < ntrials; i++) {
        // call to get mem if this condition is true
        if (rand() % 100 >= pctget) {
            if (rand() % 100 >= pctlarge) {
               inputSize = (rand() % small_limit) + 1;
            } else {
               inputSize = rand() % (large_limit - small_limit) + small_limit;
            }
            allocatedBlocks[index] = getmem(inputSize);
            index++;
        // call to free mem instead
        } else {
            if (index > 0) {
                int j = rand() % index;
                freemem(allocatedBlocks[j]);
                allocatedBlocks[j] = NULL;
                index--;
            }
        }
        // prints stats for each iteration
        int tenPercent = (int) (ntrials / 10);
        if (i != 0 && (i % tenPercent) == 0) {
            get_mem_stats(&totalAlloc, &totalFree, &freeBlocks);
            printf("Total size allocated: %lu\n", totalAlloc);
            printf("Total free size: %lu\n", totalFree);
            printf("Free blocks: %lu\n", freeBlocks);
            printf("Average bytes per free block: %lu\n",
            (uintptr_t) (totalFree / freeBlocks));
            clock_t end = clock();
            totalRunTime = (double) (end - begin) / (double) CLOCKS_PER_SEC;
            printf("Time elapsed = %f\n", totalRunTime);
        }
    }
    return 0;
}
