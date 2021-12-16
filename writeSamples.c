#include "Header.h"

// Writes sample values to a text file (or screen if section is uncommented).
void writeSamples(Histogram histogram, double *samples){

    /* ************************** */
    /* WRITE SAMPLES TO TEXT FILE */
    /* ************************** */
    
    // FILE pointer.
    FILE *file;

    // If n <= 200,000 write all samples to one file.
    if(histogram.n <= 200000){
        file = fopen("numbers.txt", "w");
        for(int i = 0; i < histogram.n; i++) fprintf(file, "%lf\n", samples[i]);
        fclose(file);
    }
    
    // Else, write samples to two separate files.
    else{
        int midPoint = histogram.n/2;
        
        // Write numbers1.txt
        file = fopen("numbers1.txt", "w");
        for(int i = 0; i < midPoint; i++) fprintf(file, "%lf\n", samples[i]);
        fclose(file);
    
        // Write numbers2.txt
        file = fopen("numbers2.txt", "w");
        for(int i = midPoint; i < histogram.n; i++) fprintf(file, "%lf\n", samples[i]);
        fclose(file);
    }
    
    /* *********************************************** */
    /* PRINT SAMPLES TO SCREEN WITH A COMMA DELIMITER  */
    /* *********************************************** */
/*
    printf("\n\t--------------");
    printf("\n\tSample Values:");
    printf("\n\t--------------\n\t");
    for(int i = 0; i < histogram.n; i++){
        if(i % 20 == 0 && i != 0) printf("\n\t");
        printf("%lf", samples[i]);
        if(i < (histogram.n-1)) printf(",\t");
    }
 */
}
