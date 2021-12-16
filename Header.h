#ifndef Header_h
#define Header_h


    /* DEFINES */


// ANSI color codes for foreground and some background colors.
#define MAGENTA     "\x1b[31m"
#define BACKMAGENTA "\e[41m\e[30m"

#define GREEN       "\x1b[1;34m"
#define BACKGREEN   "\e[0;104m\e[30m"

#define PURPLE      "\e[1;99m"
#define BACKPURPLE  "\e[48;5;129m\e[30m"

#define YELLOW      "\e[1;33m"
#define BACKYELLOW  "\e[44m\e[30m"

#define CYAN        "\x1b[33m"
#define BACKCYAN    "\e[48;5;3m\e[30m"

#define BACKGREY    "\e[47m\e[30m"

#define BLUE        "\x1b[35m"
#define PINK        "\x1b[35m"
#define MINT        "\x1b[36m"

#define RESET       "\e[0m"

// For generating random values.
#define frand() (((double)rand() + 1.) / ((double)RAND_MAX + 1.))


    /* INCLUDES */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <limits.h>
#include <unistd.h>


    /* PROCESSING.C */
void tempFunc(int *memory, int n);

// Update space from a hole to an allocated block, and update the remainder of the hole, if any.
int request(int request_size, int *memory, int n, int *mem_index, int *last_allocated, int choice);

// Update space from allocated block to a hole.
void release(int release_block, int *memory, int n);

// Coalesce all possible neighboring holes, if any.
void coalesce(int *memory, int n);

// Set the next and previous links for all holes.
void getNextAndPrev(int *memory, int n);

// Get the value of total occupied space in the 'memory' array.
int getOccupiedSpace(int *memory, int n);

// Return the last index of either an allocated block, a usable hole, or an unusable hole.
int advance(int *memory, int n, int i, bool allocated, bool usable_hole, bool UNusable_hole);

// Compare all indices of allocated blocks to release_block.
int findAllocated(int release_block, int *memory, int n);

// Print contents of memory.
void printMemory(int *memory, int n, char *flag);


    /* ALGORITHMS.C */


// First fit algorithm starts search at the beginning of the list and allocates the first hole
// large enough to accommodate the request. Function returns the number of holes examined.
int firstFit(int request_size, int *memory, int n, int *mem_index);

// Best fit algorithm searches the entire list and chooses the smallest hole large enough to
// accommodate the request. Function returns the number of holes examined.
int bestFit(int request_size, int *memory, int n, int *mem_index);

// Worst fit algorithm chooses the largest available hole for any request.
// Function returns the number of holes examined.
int worstFit(int request_size, int *memory, int n, int *mem_index);

#endif /* Header_h */
