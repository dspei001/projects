#ifndef Header_h
#define Header_h


/* ******** */
/* INCLUDES */
/* ******** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <limits.h>
#include <unistd.h>

// For seeding the random value generator.
time_t this_time;


/* *********** */
/* COLOR CODES */
/* *********** */

#define BACKGREY	"\e[47m\e[30m"			// Code 1

#define YELLOW		"\e[1;33m"				// Code 2
#define BACKYELLOW	"\e[44m\e[30m"			// Code 3

#define MAGENTA		"\x1b[31m"				// Code 4
#define BACKMAGENTA	"\e[41m\e[30m"			// Code 5

#define GREEN		"\x1b[1;34m"			// Code 6
#define BACKGREEN	"\e[0;104m\e[30m"		// Code 7

#define PURPLE		"\e[1;99m"				// Code 8
#define BACKPURPLE	"\e[48;5;129m\e[30m"	// Code 9

#define CYAN		"\x1b[33m"				// Code 10
#define BACKCYAN	"\e[48;5;3m\e[30m"		// Code 11

#define PINK		"\x1b[35m"				// Code 12
#define MINT		"\x1b[36m"				// Code 13

#define RESET		"\e[0m"


// For generating random doubles.
#define frand() (((double)rand() + 1.) / ((double)RAND_MAX + 1.))


/* ******* */
/* STRUCTS */
/* ******* */

typedef struct Block{
	// Booleans
	bool isHole;
	bool isTaken;

	// Literals
	int size;
	int next;
}Block;

typedef struct Memory{
	// Literals
	int size;
	int takenBlocksSize;
	int requestSize;
	int occupiedSpace;

	// Arrays
	int *takenBlocks;
	Block *blocks;
}Memory;

typedef struct Results{
	// Literals
	int numIterations;
	int algorithm;
	double mean;
	double stdDev;
	double numRequests;
	double amu;
	double amuCount;
	double avgHolesExamined;

	// Times
	time_t startTime;
	time_t endTime;
}Results;


/* ***************************** */
/* FUNCTIONS: MemoryProcessing.c */
/* ***************************** */

// Initializes memory to one large hole, and sets initial info.
// Prints initial memory if size <= 1000.
void setMemory(Memory *memory);

// Updates memory blocks from hole to allocated, and updates newly created holes, if any.
bool allocateBlock(Memory *memory, int thisBlock);

// Sets up holes created by the allocation process. Any neighboring holes are coalesced.
int setNewlyCreatedHole(Memory *memory, int thisBlock, int thisBlockInitialSize);

// Calculates the number of allocated blocks.
int getOccupiedSpace(Memory *memory);

// Generates random integer within range of taken array size for the release of a block.
// Block is released, block data and taken array are updated, and holes are coalesced.
void releaseBlock(Memory *memory);

// Sets the taken array with the starting indices of taken blocks.
// Used for speeding up rand() in releaseBlock().
void setTakenBlocksArray(Memory *memory);

// Combines any neighboring holes, updates new hole size, and updates next link.
// Memory is printed at the end of all coalesce operations.
void coalesceHoles(Memory *memory);


/* *********************** */
/* FUNCTIONS: Algorithms.c */
/* *********************** */

// Calls the appropriate algorithm. Each algorithm returns number of holes examined.
int runAlgorithm(Memory *memory, int algorithm, bool *go);

// Checks memory in linear fashion until the first hole that can accomodate the
// request size is found. The block is then updated from a hole to taken.
int firstFit(Memory *memory, bool *go);

// Checks the size of each hole and determines the best fit for the request size.
// The block is then updated from a hole to taken.
int bestFit(Memory *memory, bool *go);

// Checks the size of each hole and choses the largest hole that can accomodate the
// request size. The block is then updated from a hole to taken.
int worstFit(Memory *memory, bool *go);


/* *************************** */
/* FUNCTIONS: PrintUtilities.c */
/* *************************** */

// Prints a message in specified color.
void printColor(int colorCode, char *message, bool reset);

// Prints the block request size.
void printBlockRequest(int requestSize);

// Prints the holes being examined by the algorithms.
void printHoleExamined(int thisHole, int thisHoleSize);

// Prints the hole chosen for allocation by the algorithms.
void printHoleChosen(int holeChosen);

// Prints information about any newly created holes from allocation, then prints memory.
void printNewlyCreatedHole(Memory *memory, int newHole);

// Informs user that memory for the request is unavailable, then prints memory.
void printMemoryUnavailable(Memory *memory);

// Prints total occupied memory space.
void printOccupiedSpace(int occupiedSpace, int memorySize);

// Prints the block being released and its size, then prints memory.
void printBlockRelease(Memory *memory, int thisBlock, int thisBlockSize);

// Prints the holes being coalesced, their sizes, and the result.
void printCoalesceHoles(int thisHole, int thisSize, int nextHole, int nextSize);

// Prints a header before printing memory contents.
void printMemoryHeader(Memory *memory, char *title);

// Prints the contents of memory.
void printMemory(Memory *memory, int colorCode);

// Prints the final results of the simulation.
void printResults(Memory *memory, Results *results);

// Get the number of digits in index + block size.
// Used for determining correct spacing for printing memory contents.
int getNumDigits(int thisIndex, int thisSize);


#endif /* Header_h */
