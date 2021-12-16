#include "Header.h"

/*
-------------------------
 (x, n, d, v) SETS (1-4):
-------------------------
 1)    1000 16777216 1048576 262144.0
 2)    1000 16777216 4194304 1363148.8
 3)    5000 1073741824 1048576 262144.0
 4)    500 1073741824 268435456 67108864.0
*/

// TODO: FIX GETNEXTANDPREV(): AFTER FIXING THAT, REDO COALESCE TO USE LINKS. COULD RUN FASTER FOR S4.

int main(int argc, char *argv[]){
    
    // Ensure the correct arguments are given.
    if(argc != 5){
        printf("\n\n\t--------------------\n");
        printf("\tUSAGE:\t./a2 x n d v");
        printf("\n\t--------------------\n");
        printf("\n\t- Where x, n, and d are integers, and v is a float.\n");
        printf("\t- All values are required.\n\t- Ex:  ./a2 5000 1073741824 1048576 262144.0\n\n");
        return -1;
    }
    
    /* Get x, n, d, and v from command-line arguments. */
    
    int *x = (int*)malloc(sizeof(int));
    *x = strtol(argv[1], NULL, 10);

    int *n = (int*)malloc(sizeof(int));
    *n = strtol(argv[2], NULL, 10);

    double *d = (double*)malloc(sizeof(double));
    *d = strtol(argv[3], NULL, 10);

    double *v = (double*)malloc(sizeof(double));
    *v = strtol(argv[4], NULL, 10);
    
    int choice = 0;
    printf("\nChoose an algorithm to run:");
    printf("\n  [1] First Fit\n  [2] Best Fit\n  [3] Worst Fit\n");
    scanf("%d", &choice);
    
    if(choice != 1 && choice != 2 && choice != 3){
        printf("ERROR: INVALID OPTION. EXITING...\n");
        return 0;
    }
    
    // Determines while-loop continuation. Initialize to 1.
    int successful = 1;
    
    // Used for keeping track of the number of request operations.
    int num_requests = 0;
    
    // Number of times AMU was calculated before the final calculation.
    int amu_count = 0;
    
    // Used for calculating the average of the number of holes examined.
    double average_holes_examined = 0;
    
    // Used for calculating average memory utilization.
    double amu = 0;
    
    // Pointer used for saving the starting index of the last allocated space.
    int *last_allocated = (int*)malloc(sizeof(int));
    
    // Initialize last_allocated to a sentinel value, -1.
    *last_allocated = -1;
    
    // Pointer used for saving the starting index of the hole chosen by the algorithm.
    int *mem_index = (int*)malloc(sizeof(int));
    
    // Initialize mem_index to a sentinel value, -1.
    *mem_index = -1;
    
    // Pointer used as the memory space.
    int *memory = (int*)calloc(*n, sizeof(int));
    
    /* Initialize the appropriate indices of the memory array with the appropriate values. */
    
    // First and last indices get the negative version of the value of the array size which = -(n-2).
    int initial_size = ((*n)-2) * -1;
    memory[0] = initial_size;
    memory[*n-1] = initial_size;
    
    // Time variable used to seed the random value generator.
    time_t this_time;
    
    // Intialize random value generator using 'time' seed.
    srand((unsigned) time(&this_time));
    
// TODO: v
if(*n == 50) printMemory(memory, *n, "starting");

    
// ################################################################################################ //
    
    
    // Repeat x times.
    for(int i = 1; i <= *x; i++){
        
//TODO: v
printf("\nIteration: %d\n", i);
        
        // Repeat until the ability to satisfy a request is unsuccessful.
        while(successful == 1){
            
            // Generate random, normally distributed integer for the request of a new block of size S
            // with mean, d, and standard deviation, v, truncated in the range [3, (n-4)].
            int request_size = 0;
            while(request_size < 3 || request_size > (*n-4)){
              request_size = round(*d + *v * cos(2 * 3.141592 * frand()) * sqrt(-2. * log(frand())));
            }
            
            // Attempt to satisfy a request, and update the space from a hole to an allocated block.
            // Algorithms are called in request().
            int holes_examined = request(request_size, memory, *n, mem_index, last_allocated, choice);
            average_holes_examined += holes_examined;
            
            // Increment the number of requests.
            num_requests += 1;
            
            // If allocation is unsuccessful, request has failed. Break from while-loop.
            if(*mem_index < 0){
                successful = 0;
                break;
            }
        }
        
        // Get current memory utilization by first calculating the amount of occupied space.
        double occupied_space = getOccupiedSpace(memory, *n);
        
        if(occupied_space > *n) occupied_space = *n;
        
        // Add to the current value of amu, and increment amu_count for the final calculation of AMU.
        amu += (occupied_space / (*n));
        amu_count += 1;
        
        // Generate a random, uniformly distributed integer for release_block.
        int found = -1;
        int release_block = 0;
        
        // Continue generating values until a match is found.
        while(found < 0){
            
            // Limit for rand() is (n-1).
            release_block = rand() % ((*n-1) - 0) + 0;
            
            // Compare release_block to the starting indices of all allocated blocks.
            found = findAllocated(release_block, memory, *n);
            
            if(found >= 0) break;
        }
        
        // Release the chossen block, and update space from an allocated block to a hole.
        release(found, memory, *n);

        // Reset 'succcessful'.
        successful = 1;
    }
    
    // Complete the computation of the average of recorded memory utilizations.
    amu = (amu / amu_count);
    
    // Complete the computation of the average number of holes examined.
    average_holes_examined = (average_holes_examined / num_requests);
    
    // Display the final AMU, average number of holes examined, and resulting contents of memory.
    char algorithm[10];
    if(choice == 1) strcpy(algorithm, "FIRST FIT");
    else if(choice == 2) strcpy(algorithm, "BEST FIT");
    else if(choice == 3) strcpy(algorithm, "WORST FIT");
    
    printf("\n\n\t\e[44m\e[30m FINAL RESULTS: %s \e[0m", algorithm);
    printf("\n\tAMU FINAL: %.3f", amu);
    printf("\n\tAVG HOLES EXAMINED: %.3f\n\n", average_holes_examined);

// TODO: v
if(*n == 50) printMemory(memory, *n, "resulting");
    
    
// ################################################################################################ //
    
    
    // Free the memory allocated to all dynamically allocated variables and arrays.
    free(x);
    free(n);
    free(d);
    free(v);
    free(memory);
    free(mem_index);
    free(last_allocated);
            
    // End program with a newline and exit.
    printf("\n");
    exit(0);
}
