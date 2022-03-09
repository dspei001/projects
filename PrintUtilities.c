#include "Header.h"

/**
 * Prints a message in specified color.
 * @param colorCode
 * @param message
 * @param reset : Boolean to determine whether to reset the color.
 */
void printColor(int colorCode, char *message, bool reset){

	if(colorCode == 0) printf("%s", message);
	else if(colorCode == 1) printf(BACKGREY "%s", message);
	else if(colorCode == 2) printf(YELLOW "%s", message);
	else if(colorCode == 3) printf(BACKYELLOW "%s", message);
	else if(colorCode == 4) printf(MAGENTA "%s", message);
	else if(colorCode == 5) printf(BACKMAGENTA "%s", message);
	else if(colorCode == 6) printf(GREEN "%s", message);
	else if(colorCode == 7) printf(BACKGREEN "%s", message);
	else if(colorCode == 8) printf(PURPLE "%s", message);
	else if(colorCode == 9) printf(BACKPURPLE "%s", message);
	else if(colorCode == 10) printf(CYAN "%s", message);
	else if(colorCode == 11) printf(BACKCYAN "%s", message);
	else if(colorCode == 12) printf(PINK "%s", message);
	else if(colorCode == 13) printf(MINT "%s", message);
	if(reset) printf(RESET);
}

/**
 * Prints the block request size.
 * @param requestSize
 */
void printBlockRequest(int requestSize){

	char msg[100] = {"\0"};
	sprintf(msg, "\nRequesting block of size %d.", requestSize);
	printColor(2, msg, true);
}

/**
 * Prints the holes being examined by the algorithms.
 * @param thisHole
 * @param thisHoleSize
 */
void printHoleExamined(int thisHole, int thisHoleSize){

	char msg[100] = {"\0"};
	sprintf(msg, "\n\tChecking block %d  |  Size: [%d]", thisHole, thisHoleSize);
	printColor(12, msg, true);
}

/**
 * Prints the hole chosen for allocation by the algorithms.
 * @param holeChosen
 */
void printHoleChosen(int holeChosen){

	char msg[100] = {"\0"};
	sprintf(msg, "\nBlock %d chosen.\n", holeChosen);
	printColor(2, msg, true);
}

/**
 * Prints information about any newly created holes from allocation, then prints memory.
 * @param memory : Memory struct.
 * @param : newHole
 */
void printNewlyCreatedHole(Memory *memory, int newHole){

	int newHoleSize = memory->blocks[newHole].size;
	char msg[100] = {"\0"};
	sprintf(msg, "\nNew hole created at %d | Size: [%d].\n", newHole, newHoleSize);
	printColor(10, msg, true);
	if(memory->size <= 1000) printMemoryHeader(memory, "new hole");
}

/**
 * Informs user that memory for the request is unavailable, then prints memory.
 * @param memory : Memory struct.
 */
void printMemoryUnavailable(Memory *memory){

	printColor(4, "\n\n(!) MEMORY UNAVAILABLE (!)\n", true);
	if(memory->size <= 1000) printMemoryHeader(memory, "unavailable");
}

/**
 * Prints total occupied memory space.
 * @param occupiedSpace
 * @param memorySize
 */
void printOccupiedSpace(int occupiedSpace, int memorySize){

	char msg[100] = {"\0"};
	sprintf(msg, "\nOccupied Space: %d of %d\n", occupiedSpace, memorySize);
	printColor(6, msg, true);
}

/**
 * Prints the block being released and its size, then prints memory.
 * @param memory : Memory struct.
 * @param thisBlock
 * @param thisBlockSize
 */
void printBlockRelease(Memory *memory, int thisBlock, int thisBlockSize){

	char msg[100];
	sprintf(msg, "Releasing block %d | Size: [%d]\n", thisBlock, thisBlockSize);
	printColor(6, msg, true);
	if(memory->size <= 1000) printMemoryHeader(memory, "release");
}

/**
 * Prints the holes being coalesced, their sizes, and the result.
 * @param thisHole
 * @param thisSize
 * @param nextHole
 * @param nextSize
 */
void printCoalesceHoles(int thisHole, int thisSize, int nextHole, int nextSize){

	char msg[150] = {"\0"};
	sprintf(msg, "\nCoalesce: (Hole %d | Size: [%d])", thisHole, thisSize);
	printColor(8, msg, false);
	sprintf(msg, " + (Hole %d | Size: [%d])", nextHole, nextSize);
	printColor(8, msg, false);
	int totalSize = thisSize + nextSize;
	sprintf(msg, "\nResult: Hole %d | Size: [%d]\n", thisHole, totalSize);
	printColor(8, msg, true);
}

/**
 * Prints a header before printing memory contents.
 * @param memory : Memory struct.
 * @param title : Header title before memory contents.
 */
void printMemoryHeader(Memory *memory, char *title){

	int colorCode = 0;

	// Print header in certain colors depending on where this function was called.
	printf("\n\n\t -------");
	if(strcmp(title, "initial") == 0){
		colorCode = 0;
		printColor(1, " INITIAL MEMORY ", true);
	}
	else if(strcmp(title, "resulting") == 0){
		colorCode = 2;
		printColor(3, " MEMORY RESULT ", true);
	}
	else if(strcmp(title, "new hole") == 0){
		colorCode = 10;
		printColor(11, " CURRENT MEMORY ", true);
	}
	else if(strcmp(title, "unavailable") == 0){
		colorCode = 4;
		printColor(5, " CURRENT MEMORY ", true);
	}
	else if(strcmp(title, "release") == 0){
		colorCode = 6;
		printColor(7, " CURRENT MEMORY ", true);
	}
	else if(strcmp(title, "coalesce") == 0){
		colorCode = 8;
		printColor(9, " CURRENT MEMORY ", true);
	}
	for(int i = 0; i < 42; i++) printf("-");
	printf("\n\t|                                                                 |\n");

	// Print starting indices of each block in the same color as the header.
	printMemory(memory, colorCode);
}

/**
 * Prints the contents of memory.
 * @param memory : Memory struct.
 * @param colorCode : For printing starting indices of each block in a specific color.
 */

void printMemory(Memory *memory, int colorCode){

	// Print memory contents evenly spaced in a text box.
	int width = 0;
	char widthHolder = ' ';
	int numDigits = 0;

	// Print first index of the block containing size.
	for(int i = 0; i < memory->size; i += memory->blocks[i].size){

		// Get number of digits in index and size for consistent spacing.
		numDigits = getNumDigits(i, memory->blocks[i].size);
		if(numDigits == 6) width = 4;
		else if(numDigits == 5) width = 5;
		else if(numDigits == 4) width = 6;
		else if(numDigits == 3) width = 7;
		else if(numDigits == 2) width = 8;

		if(i % 5 == 0){ // Line beg
			printf("\t|   ");
			printColor(colorCode, "", false);
			printf("%d [%d]%*c", i, memory->blocks[i].size, width, widthHolder);
			printf(RESET);
		}
		else if(i % 5 > 0 && i % 5 < 4){ // Line mid
			printColor(colorCode, "", false);
			printf("%d [%d]%*c", i, memory->blocks[i].size, width, widthHolder);
			printf(RESET);
		}
		else if(i % 5 == 4){ // Line end
			printColor(colorCode, "", false);
			printf("%d [%d]", i, memory->blocks[i].size);
			printf(RESET);
			if(numDigits == 6) printf(" |\n");
			else if(numDigits == 5) printf("  |\n");
			else if(numDigits == 4) printf("   |\n");
			else if(numDigits == 3) printf("    |\n");
			else if(numDigits == 2) printf("     |\n");
		}

		// Print the inside of the block: [  ] if hole, [ *] if allocated.
		for(int j = (i+1); j < (i+memory->blocks[i].size); j++){

			// Get number of digits in index and contents for consistent spacing.
			numDigits = getNumDigits(j, 2)+1;
			if(numDigits == 3) width = 7;
			else if(numDigits == 4) width = 6;
			else if(numDigits == 5) width = 5;

			if(j % 5 == 0){ // Line beg
				if(memory->blocks[i].isHole) 
					printf("\t|   %d [  ]%*c", j, width, widthHolder);
				else if(memory->blocks[i].isTaken) 
					printf("\t|   %d [ *]%*c", j, width, widthHolder);
			}
			else if(j % 5 > 0 && j % 5 < 4){ // Line mid
				if(memory->blocks[i].isHole) 
					printf("%d [  ]%*c", j, width, widthHolder);
				else if(memory->blocks[i].isTaken) 
					printf("%d [ *]%*c", j, width, widthHolder);
			}
			else if(j % 5 == 4){ // Line end
				if(memory->blocks[i].isHole) printf("%d [  ]", j);
				else if(memory->blocks[i].isTaken) printf("%d [ *]", j);
				if(numDigits == 3) printf("    |\n");
				else if(numDigits == 4) printf("   |\n");
				else if(numDigits == 5) printf("  |\n");
			}
		}
	}
	printf("\t|                                                                 |\n\t ");
	for(int i = 0; i < 65; i++) printf("-");
	printf("\n");
}

/**
 * Prints the final results of the simulation.
 * @param memory : Memory struct.
 * @param results : Results struct.
 */
void printResults(Memory *memory, Results *results){

	results->endTime = time(NULL);
	if(memory->size <= 100) printMemoryHeader(memory, "resulting");	
	printf("\n\n\t");

	if(results->algorithm == 1) printColor(3, " FINAL RESULTS: FIRST FIT ", true);
	else if(results->algorithm == 2) printColor(3, " FINAL RESULTS: BEST FIT ", true);
	else if(results->algorithm == 3)  printColor(3, " FINAL RESULTS: WORST FIT ", true);

	printColor(2, "\n\tAMU FINAL: ", true);
	printf("%.3f", results->amu);

	printColor(2, "\n\tAVG HOLES EXAMINED: ", true);
	printf("%.3f", results->avgHolesExamined);

	printColor(2, "\n\tTOTAL EXECUTION TIME: ", true);
	printf("%ld second(s)\n\n\n\t", (results->endTime - results->startTime));
}

/**
 * Get the number of digits in index + block size. 
 * Used for determining correct spacing for printing memory contents.
 * @param thisIndex
 * @param thisSize
 * @return numDigits
 */
int getNumDigits(int thisIndex, int thisSize){

	int indexDigitCount = 0;
	int sizeDigitCount = 0;

	if(thisIndex <= 9) indexDigitCount = 1;
	else if(thisIndex <= 99 && thisIndex >= 10) indexDigitCount = 2;
	else if(thisIndex <= 999 && thisIndex >= 100) indexDigitCount = 3;

	if(thisSize <= 9) sizeDigitCount = 1;
	else if(thisSize <= 99 && thisSize >= 10) sizeDigitCount = 2;
	else if(thisSize <= 999 && thisSize >= 100) sizeDigitCount = 3;

	return (indexDigitCount + sizeDigitCount);
}