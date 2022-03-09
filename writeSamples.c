#include "Header.h"

/**
 * Calls a function to write sample values to file depending on number of samples.
 * @param histogram : Pointer to Histogram struct.
 */
void writeSamples(Histogram *histogram){

    // If n <= 200,000 write all samples to one file. Else, two separate files.
    if(histogram->n <= 200000) writeOneFile(histogram);
    else if(histogram->n > 200000) writeTwoFiles(histogram);
}

/**
 * Writes all sample values to one text file.
 * @param histogram : Pointer to Histogram struct.
 */
void writeOneFile(Histogram *histogram){

	FILE *file = fopen("numbers.txt", "w");
    for(int i = 0; i < histogram->n; i++) fprintf(file, "%f\n", histogram->samples[i]);
    fclose(file);
}

/**
 * Writes all sample values to two text files; half on one, half on the other.
 * @param histogram : Pointer to Histogram struct.
 */
void writeTwoFiles(Histogram *histogram){

    int midPoint = histogram->n/2;

    // Write numbers1.txt
    FILE *file = fopen("numbers1.txt", "w");
    for(int i = 0; i < midPoint; i++) fprintf(file, "%f\n", histogram->samples[i]);
    fclose(file);

    // Write numbers2.txt
    file = fopen("numbers2.txt", "w");
    for(int i = midPoint; i < histogram->n; i++) fprintf(file, "%f\n", histogram->samples[i]);
    fclose(file);
}