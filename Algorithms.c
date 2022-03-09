#include "Header.h"

/**
 * Calls the appropriate algorithm. Each algorithm returns number of holes examined.
 * @param memory : Memory struct.
 * @param algorithm : The code corresponding to the user-selected algorithm.
 * @param go : Boolean to determine if request has been satisfied.
 * @return holesExamined : Returned by the chosen algorithm.
 */
int runAlgorithm(Memory *memory, int algorithm, bool *go){

	int holesExamined = 0;
	*go = false;

	// Print block request size.
	printBlockRequest(memory->requestSize);

	// Run chosen algorithm.
	if(algorithm == 1) holesExamined = firstFit(memory, go);
	else if(algorithm == 2) holesExamined = bestFit(memory, go);
	else if(algorithm == 3) holesExamined = worstFit(memory, go);

	// If request could not be satisfied, inform user. Also prints memory if size <= 100.
	if(*go == false) printMemoryUnavailable(memory);

	return holesExamined;
}

/**
 * Checks memory in linear fashion until the first hole that can accomodate the 
 * request size is found. The block is then updated from a hole to taken.
 * @param memory : Memory struct.
 * @param go : Boolean to determine if request has been satisfied.
 * @return holesExamined
 */
int firstFit(Memory *memory, bool *go){

	int holesExamined = 0;

	for(int i = 0; i < memory->size; i += memory->blocks[i].size){
		if(memory->blocks[i].isHole){
			holesExamined++;

			// Print hole being examined.
			printHoleExamined(i, memory->blocks[i].size);

			// If space is available in this hole, allocate it and break.
			if(memory->blocks[i].size >= memory->requestSize){
				*go = allocateBlock(memory, i);
				break;
			}
		}
	}

	return holesExamined;
}

/**
 * Checks the size of each hole and determines the best fit for the request size.
 * The block is then updated from a hole to taken.
 * @param memory : Memory struct.
 * @param go : Boolean to determine if request has been satisfied.
 * @return holesExamined
 */
int bestFit(Memory *memory, bool *go){

	int holesExamined = 0;
	int bestFit = -1;

	for(int i = 0; i < memory->size; i += memory->blocks[i].size){
		if(memory->blocks[i].isHole){
			holesExamined++;

			// Print hole being examined.
			printHoleExamined(i, memory->blocks[i].size);

			// If space is available in this hole, check if it is the best fit so far.
			if(memory->blocks[i].size >= memory->requestSize){
				if(bestFit == -1) bestFit = i;
				if(memory->blocks[i].size < memory->blocks[bestFit].size) bestFit = i;
			}
		}
	}

	// If a block is chosen, print it and allocate it.
	if(bestFit > -1) *go = allocateBlock(memory, bestFit);

	return holesExamined;
}

/**
 * Checks the size of each hole and choses the largest hole that can accomodate the 
 * request size. The block is then updated from a hole to taken.
 * @param memory : Memory struct.
 * @param go : Boolean to determine if request has been satisfied.
 * @return holesExamined
 */
int worstFit(Memory *memory, bool *go){

	int holesExamined = 0;
	int worstFit = -1;

	for(int i = 0; i < memory->size; i += memory->blocks[i].size){
		if(memory->blocks[i].isHole){
			holesExamined++;

			// Print hole being examined.
			printHoleExamined(i, memory->blocks[i].size);

			// If space is available in this hole, check if it is the worst fit so far.
			if(memory->blocks[i].size >= memory->requestSize){
				if(worstFit == -1) worstFit = i;
				if(memory->blocks[i].size > memory->blocks[worstFit].size) worstFit = i;
			}
		}
	}

	// If a block is chosen, print it and allocate it.
	if(worstFit > -1) *go = allocateBlock(memory, worstFit);

	return holesExamined;
}
