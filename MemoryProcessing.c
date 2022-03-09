#include "Header.h"

/**
 * Initializes memory to one large hole, and sets initial info.
 * Prints initial memory if size <= 1000.
 * @param memory : Memory struct.
 */
void setMemory(Memory *memory){

	memory->takenBlocksSize = 1;
	memory->takenBlocks = (int*)malloc(memory->takenBlocksSize * sizeof(int));
	memory->blocks = (Block*)malloc(memory->size * sizeof(Block));

	memory->blocks[0].isHole = true;
	memory->blocks[0].isTaken = false;
	memory->blocks[0].size = memory->size;
	memory->blocks[0].next = 0;

	if(memory->size <= 1000) printMemoryHeader(memory, "initial");
}

/**
 * Updates memory blocks from hole to allocated, and updates newly created holes, if any.
 * @param memory : Memory struct.
 * @param thisBlock : Memory index of block to allocate.
 * @return true upon successful allocation.
 */
bool allocateBlock(Memory *memory, int thisBlock){

	int thisBlockInitialSize = memory->blocks[thisBlock].size;

	// Set this block as allocated, and update its size and its taken array.
	memory->blocks[thisBlock].isHole = false;
	memory->blocks[thisBlock].isTaken = true;
	memory->blocks[thisBlock].size = memory->requestSize;
	memory->takenBlocksSize++;
	memory->takenBlocks = realloc(memory->takenBlocks, memory->takenBlocksSize);
	memory->takenBlocks[memory->takenBlocksSize-1] = thisBlock;

	// Set next link of last block to 0 (first block).
	if(thisBlock + memory->blocks[thisBlock].size == memory->size-1)
		memory->blocks[thisBlock].next = 0;

	// Print hole chosen.
	printHoleChosen(thisBlock);

	// Set up the newly created hole, if any, and print new hole info.
	if(memory->requestSize < thisBlockInitialSize){
		int newHole = setNewlyCreatedHole(memory, thisBlock, thisBlockInitialSize);
		printNewlyCreatedHole(memory, newHole);
	}

	return true;
}

/**
 * Sets up holes created by the allocation process. Any neighboring holes are coalesced.
 * @param memory : Memory struct.
 * @param thisBlock : For determining size of new hole.
 * @param thisBlockInitialSize : For determining size of new hole.
 * @return newHole
 */
int setNewlyCreatedHole(Memory *memory, int thisBlock, int thisBlockInitialSize){

	int newHole = thisBlock + memory->blocks[thisBlock].size;

	memory->blocks[newHole].isHole = true;
	memory->blocks[newHole].isTaken = false;
	memory->blocks[newHole].size = thisBlockInitialSize - memory->requestSize;
	memory->blocks[newHole].next = memory->blocks[thisBlock].next;
	memory->blocks[thisBlock].next = newHole;

	coalesceHoles(memory);

	return newHole;
}

/**
 * Calculates the number of allocated blocks.
 * @param memory : Memory struct.
 * @return occupiedSpace
 */
int getOccupiedSpace(Memory *memory){

	int occupiedSpace = 0;

	for(int i = 0; i < memory->size; i += memory->blocks[i].size)
		if(memory->blocks[i].isTaken)
			occupiedSpace += memory->blocks[i].size;

	// Print space occupied relative to total memory size and return.
	printOccupiedSpace(occupiedSpace, memory->size);

	return occupiedSpace;
}

/**
 * Generates random integer within range of taken array size for the release of a block.
 * Block is released, block data and taken array are updated, and holes are coalesced.
 * @param memory : Memory struct.
 */
void releaseBlock(Memory *memory){

	while(1){
		// Generate uniformly distributed integer for the release block number.
		int releaseThisBlock = rand() % memory->takenBlocksSize;

		// If taken, designate as a hole, print info, and coalesce any neighboring holes.
		if(memory->blocks[memory->takenBlocks[releaseThisBlock]].isTaken){
			memory->blocks[memory->takenBlocks[releaseThisBlock]].isTaken = false;
			memory->blocks[memory->takenBlocks[releaseThisBlock]].isHole = true;

			// Print block release. Also prints memory if memory size <= 100.
			int thisBlock = memory->takenBlocks[releaseThisBlock];
			int thisBlockSize = memory->blocks[thisBlock].size;
			printBlockRelease(memory, thisBlock, thisBlockSize);

			// Coalesce any neighboring holes and break.
			coalesceHoles(memory);
			break;
		}
	}

	// Update taken array.
	setTakenBlocksArray(memory);
}

/**
 * Sets the taken array with the starting indices of taken blocks.
 * Used for speeding up rand() in releaseBlock().
 * @param memory : Memory struct.
 */
void setTakenBlocksArray(Memory *memory){

	int arrSize = 0;
	
	for(int i = 0; i < memory->size; i += memory->blocks[i].size){
		if(memory->blocks[i].isTaken){
			arrSize++;
			memory->takenBlocks = realloc(memory->takenBlocks, arrSize);
			memory->takenBlocks[arrSize-1] = i;
			memory->takenBlocksSize = arrSize;
		}
	}
}

/**
 * Combines any neighboring holes, updates new hole size, and updates next link.
 * Memory is printed at the end of all coalesce operations.
 * @param memory : Memory struct.
 */
void coalesceHoles(Memory *memory){

	bool changeMade = false;

	for(int i = 0; i < memory->size; i += memory->blocks[i].size){
		int thisBlock = i, nextBlock = 0;

		// If this is not the last block, get next block.
		if(thisBlock + memory->blocks[thisBlock].size != memory->size-1)
			nextBlock = thisBlock + memory->blocks[thisBlock].size;
		else break;

		// Combine the blocks if both are holes. Continue if more neighboring holes.
		while(1){
			if(memory->blocks[thisBlock].isHole && memory->blocks[nextBlock].isHole){
				int thisSize = memory->blocks[thisBlock].size;
				int nextSize = memory->blocks[nextBlock].size;

				// Print holes being coalesced and the result.
				printCoalesceHoles(thisBlock, thisSize, nextBlock, nextSize);

				// Increase combine sizes of the holes into one hole.
				memory->blocks[thisBlock].size += memory->blocks[nextBlock].size;
				thisSize = memory->blocks[thisBlock].size;

				// Set next link. If this hole is the last block, next = 0.
				if(thisBlock + thisSize == memory->size-1) 
					memory->blocks[thisBlock].next = 0;
				else 
					memory->blocks[thisBlock].next = thisBlock + thisSize;

				// If this is not the last block, get the next block. Else break.
				if(memory->blocks[thisBlock].next != 0)
					nextBlock = memory->blocks[thisBlock].next;
				else break;

				changeMade = true;
			}
			else break;
		}
	}

	if(changeMade && memory->size <= 1000) printMemoryHeader(memory, "coalesce");
}
