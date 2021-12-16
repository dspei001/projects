#include "Header.h"

// Calculates the population mean and std dev and displays the results.
void meanAndStdDev(Histogram histogram, double *samples){
    
    // Double variables, sum, mean, and stdDev initiated with 0.00.
    double sum = 0.00;
    double mean = 0.00;
    double stdDev = 0.00;
    
    // Calculate the sum of all samples.
    for(int i = 0; i < histogram.n; i++) sum += samples[i];
    
    // Calculate the mean of all samples.
    mean = sum / (double)histogram.n;
    
    // Calculate the standard deviation of all samples.
    for(int i = 0; i < histogram.n; i++) stdDev += (double)pow(samples[i] - mean, 2.0);

    stdDev = (double)sqrt(stdDev / (histogram.n-1));
    
    // Display results in the chosen color theme.
    printf("\n\n\t---------------------------\n");
    if(histogram.colorTheme == 1) printf(COLOR1 "\tPopulation Mean and StdDev:");
    if(histogram.colorTheme == 2) printf(COLOR5 "\tPopulation Mean and StdDev:");
    if(histogram.colorTheme == 3) printf(COLOR9 "\tPopulation Mean and StdDev:");
    if(histogram.colorTheme == 4) printf(COLOR13 "\tPopulation Mean and StdDev:");
    if(histogram.colorTheme == 5) printf(COLOR17 "\tPopulation Mean and StdDev:");
    if(histogram.colorTheme == 6) printf(COLOR21 "\tPopulation Mean and StdDev:");
    printf(RESET);
    printf("\n\t---------------------------");
    printf("\n\tPopulation Mean: %.5f\n", mean);
    printf("\tPopulation Standard Deviation: %.5f\n", stdDev);
}
