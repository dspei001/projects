#include "Header.h"

// For generating random doubles.
#define frand() (double)rand()/(double)(RAND_MAX/1.00)

// Used for seeding the random value generator.
time_t thisTime;

/**
 * Sets range for sample generation and runs distribution method based on user input.
 * @param histogram : Pointer to Histogram struct.
 */
void generateSamples(Histogram *histogram){

    // Holds the sample value range.
	int range = 0;

	// Set the size of *samples relative to sample size, histogram->n.
    histogram->samples = (double*)calloc(histogram->n, sizeof(double));

	// Generate range based on whether lower/upper values are negative/positive.
    if(histogram->m < 0) range = ((int)histogram->M - (int)histogram->m) + 1;
    else if(histogram->m >= 0) range = (int)histogram->M + (int)histogram->m + 1;
	if(histogram->M < 0) range = (int)(histogram->M * -1) + (int)(histogram->m * -1) + 1;

	// Generate samples given uniform distribution or normal distribution.
	if(histogram->distribution == 1) uniformDistribution(histogram, range);
	else if(histogram->distribution == 2) normalDistribution(histogram);
}

/**
 * Generates histogram sample values using uniform distribution.
 * @param histogram : Pointer to Histogram struct.
 * @param range : range for sample value generation calculated in generateSamples().
 */
void uniformDistribution(Histogram *histogram, int range){

    // Used for temporarily holding sample value.
    int temp = 0;

    // Initialize random value generator.
    srand((unsigned) time(&thisTime));

    // Generate n samples.
    for(int i = 0; i < histogram->n; i++){
        rand();

        // Generate uniformly distributed numbers in the range of [m, M].
        temp = (int)histogram->m - 1;
		while(temp < histogram->m || temp > histogram->M){
			if(histogram->m >= 0) 
				temp = rand() % (int)((histogram->M - histogram->m + 1) + histogram->m);
			else temp = (rand() % range) - (int)(histogram->m * -1);
		}
		histogram->samples[i] = temp;

// FOR TESTING.
//if(temp == histogram->m || temp == histogram->M) printf("\nTEMP: %f", (double)temp);
	}
}

/**
 * Generates histogram sample values using normal distribution.
 * @param histogram : Pointer to Histogram struct.
 */
void normalDistribution(Histogram *histogram){

	// Used for temporarily holding sample value.
	double temp = 0.00000;

    // Initialize random value generator.
    srand((unsigned) time(&thisTime));

	// Generate n samples of normally distributed random numbers with mean, mu,
	// and standard deviation, sigma truncated in the range of [m, M).
	for(int i = 0; i < histogram->n; i++){
		temp = histogram->m - 1;
		while(temp < histogram->m || temp > histogram->M){
			temp = histogram->mu + histogram->sigma 
				* cos(2 * 3.141592 * frand()) * sqrt(-2. * log(frand()));
		}
		histogram->samples[i] = temp;

// FOR TESTING --> UPDATE: STILL NO INCLUSIVITY.
// TRY TO GET IT TO INCLUDE (AT LEAST) LOWER BOUND.
//if(temp == histogram->m || temp == histogram->M) printf("\nTEMP: %f", temp);
	}
}