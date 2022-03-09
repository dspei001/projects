#include "Header.h"

/**
 * Runs the memory allocation simulation.
 * @param memory : Memory struct.
 * @param results : Results struct.
 */
void runSimulation(Memory *memory, Results *results){

	// Repeat until the ability to satisfy a request is unsuccessful.
	bool *go = (bool*)malloc(sizeof(bool));

	// Seed the random value generator.
	srand((unsigned) time(&this_time));

	for(int i = 1; i <= results->numIterations; i++){
		printf("\n\t\t\t\t\t\t\t\t\t\tIteration: %d\n", i);

		*go = true;
		while(*go){
			rand();

			// Generate random, normally distributed integer for request size
			// given mean and standard deviation truncated in range [1, (memSize-1)].
			memory->requestSize = 0;
			while(memory->requestSize < 1 || memory->requestSize > (memory->size-1)){
				memory->requestSize = round(results->mean + results->stdDev 
											* cos(2 * 3.141592 * frand()) 
											* sqrt(-2. * log(frand())));
			}

			// Increment average holes examined, run algorithm, and increment #requests.
			results->avgHolesExamined += runAlgorithm(memory, results->algorithm, go);
			results->numRequests++;
		}

		// Get occupied space, add to amu and amu count, and release a block.
		memory->occupiedSpace = getOccupiedSpace(memory);
		results->amu += ((double)memory->occupiedSpace / (double)memory->size);
		results->amuCount++;
		releaseBlock(memory);
	}

	// Complete computations for amu and average holes examined.
	results->amu /= results->amuCount;
	results->avgHolesExamined /= (double)results->numRequests;
}

int main(int argc, char *argv[]){

	// Ensure the correct arguments are given.
	if(argc != 5){
		printf("\n  "); for(int i = 0; i < 83; i++) printf("-");
		printf("\n  USAGE:  ./Memory Allocation Simulator ");
		printf("[# iterations] [memory size] [mean] [std dev]\n  ");
		for(int i = 0; i < 83; i++) printf("-");
		printf("\n  - All values are required.");
		printf("\n  - Ex:  ./Memory Allocation Simulator");
		printf(" 5000 1073741824 1048576 262144.0\n\n");
		exit(-1);
	}

	// Declare the Results and Memory structs.
	Results *results = (Results*)malloc(sizeof(Results));
	Memory *memory = (Memory*)malloc(sizeof(Memory));

	// Get command-line arguments. Set initial variables memory size and results.
	results->numIterations = *(int*)malloc(sizeof(int));
	results->numIterations = strtol(argv[1], NULL, 10);

	memory->size = *(int*)malloc(sizeof(int));
	memory->size = strtol(argv[2], NULL, 10);

	results->mean = *(double*)malloc(sizeof(double));
	results->mean = strtol(argv[3], NULL, 10);

	results->stdDev = *(double*)malloc(sizeof(double));
	results->stdDev = strtol(argv[4], NULL, 10);

	// Get algorithm choice from user.
	results->algorithm = 0;
	printf("\nChoose an algorithm to run:");
	printf("\n  [1] First Fit\n  [2] Best Fit\n  [3] Worst Fit\n");
	scanf("%d", &results->algorithm);
	if(results->algorithm < 1 || results->algorithm > 3) exit(1);

	// Set and print initial memory.
	setMemory(memory);

	// Begin simulation, and print results.
	results->startTime = time(NULL);
	runSimulation(memory, results);
	printResults(memory, results);

	// Free memory and exit.
	free(results);
	free(memory);
	exit(0);
}