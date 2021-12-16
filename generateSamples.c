#include "Header.h"

// For generating random doubles.
// Credit (assumed): Kianoosh Boroojeni (FIU)
#define frand() (double)rand()/(double)(RAND_MAX/1.00)

// Generates samples based on the user-selected method of sample generation.
void generateSamples(Histogram histogram, double *samples){
    
    // time_t variable, thisTime, is used to seed the random value generator.
    time_t thisTime;

    // Intialize random value generator.
    srand((unsigned) time(&thisTime));
    
    // Int, range, holds the range of the upper and lower sample value range.
    // NOTE: The value of 'range' depends on the polarity of min and max.
    int range = 0;
    if(histogram.m < 0){
        range = ((int)histogram.M - (int)histogram.m + 1);
        if(histogram.M < 0){
            range = ((int)(histogram.M * -1) + (int)(histogram.m * -1) + 1);
        }
    }
    else if(histogram.m >= 0) range = ((int)histogram.M + (int)histogram.m + 1);
    
    // Int, temp1, temporarily holds sample value for option 1.
    int temp1 = 0;
    
    // Double, temp2, temporarily holds sample value for option 2.
    double temp2 = 0.00000;
    
    /* **************** */
    /* GENERATE SAMPLES */
    /* **************** */
    
    // Generate n samples.
    for(int i = 0; i < histogram.n; i++){
        rand();
  
        /* ******** */
        /* OPTION 1 */
        /* ******** */

        // Generate uniformly distributed numbers in the range of [m, M].
        if(histogram.option == 1){
            temp1 = (int)histogram.m - 1;
            while(temp1 < histogram.m || temp1 > histogram.M){
                if(histogram.m >= 0) temp1 = rand() % range;
                else temp1 = (rand() % range) - (histogram.m * -1);
            }
            samples[i] = temp1;
// TODO
//printf("SAMPLES[%d]: %lf\n", i, samples[i]);
//if(temp1 == -100 || temp1 == 100) printf("TEMP1: %d\n", temp1);
            
        }

        /* ******** */
        /* OPTION 2 */
        /* ******** */
        
        // Generate normally distributed random numbers with mean, mu, and standard
        // deviation, sigma truncated in the range of [m, M].
        else if(histogram.option == 2){
            temp2 = histogram.m - 1;
            while(temp2 < histogram.m || temp2 > histogram.M){
                temp2 = histogram.mu + histogram.sigma * cos(2 * 3.141592 * frand()) * sqrt(-2. * log(frand()));
            }
            samples[i] = temp2;
        }
    }
}
