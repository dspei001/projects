#include "Header.h"

// Prints a vertical histogram, most-used bin, bins, ranges for each bin, and number
// of samples that fell into each bin. Calls meanAndStdDev().
void createHistogram(Histogram histogram, double *samples){

    // Double array, ranges, saves the ranges used for each bin.
    double ranges[histogram.bins][2];
    
    // Int array pointer, bins, holds the number of samples that fall into each bin.
    int *bins;
    
    // Char array pointer, values, holds '|' if a bin was used or ' ' if not.
    char *values;
    
    // Bool, modified, is used if the number of bins selected needed to be modified.
    bool modified = false;
    
    /* ************* */
    /* SET BIN WIDTH */
    /* ************* */

    // Find range between the upper and lower sample value ranges.
    double sampleRange = histogram.M - histogram.m;
    if(sampleRange < 0) sampleRange *= -1;
    
    // Calculate the bin width.
    histogram.binWidth = sampleRange / (double)histogram.bins;
    if(histogram.binWidth == 0.00000) histogram.binWidth = 0.000001;
    
    /* ************** */
    /* SET BIN RANGES */
    /* ************** */
    
    // First value of the first range is the minimum sample value.
    ranges[0][0] = histogram.M;
    for(int i = 0; i < histogram.n; i++)
        if(samples[i] < ranges[0][0]) ranges[0][0] = samples[i];
    
    // The second value of the first range is the minimum sample value + bin width.
    ranges[0][1] = ranges[0][0] + histogram.binWidth;

    // Last value of the last range is M.
    ranges[histogram.bins-1][1] = histogram.M;

    // If it is not possible to fill all bin ranges with the calculated bin width,
    // histogram.bins is modified.
    for(int i = 1; i < histogram.bins; i++){
        
        ranges[i][0] = ranges[i-1][1] + 0.000001;
        ranges[i][1] = ranges[i][0] + histogram.binWidth;
        
        if(i == histogram.bins-2){
            ranges[i+1][0] = ranges[i][1] + 0.000001;
            ranges[i+1][1] = histogram.M;
            break;
        }
        
        if(ranges[i][0] >= histogram.M){
            ranges[i][0] = histogram.M;
            ranges[i][1] = histogram.M;
            histogram.bins = i + 1;
            modified = true;
            break;
        }
        
        else if(ranges[i][1] >= histogram.M){
            ranges[i][1] = histogram.M;
            histogram.bins = i + 1;
            modified = true;
            break;
        }
    }

    /* ********* */
    /* MARK BINS */
    /* ********* */
    
    // Get each generated value from samples[], and add to the appropriate bins.
    bins = (int*)calloc(histogram.bins, sizeof(int));
    for(int i = 0; i < histogram.n; i++){
        for(int j = 0; j < histogram.bins; j++){
            if(histogram.option == 1){
                if((double)samples[i] >= ranges[j][0] && (double)samples[i] <= ranges[j][1]){
                    bins[j]++;
                    break;
                }
            }
            
            else if(histogram.option == 2){
                if(samples[i] >= ranges[j][0] && samples[i] <= ranges[j][1]){
                    bins[j]++;
                }
            }
        }
    }
    
    /* *********************** */
    /* SET HISTOGRAM STRUCTURE */
    /* *********************** */
    
    // Find the max value in bins[] to minimize empty space above the histogram.
    int maxVal = 0;
    int maxBin = 0;
    for(int i = 0; i < histogram.bins; i++){
        if(bins[i] > maxVal){
            maxVal = bins[i];
            maxBin = i;
        }
    }

    // Determine when to save a space or a vertical bar to values[].
    values = (char *)malloc(histogram.n * histogram.bins * sizeof(char));
    int size = 0;
    for(int i = 0; i < histogram.bins; i++){
        size = (histogram.n - bins[i] - 1);
        for(int j = 0; j <= size; j++) *(values + (j * histogram.bins) + i) = ' ';
        for(int k = (size+1); k < histogram.n; k++) *(values + (k * histogram.bins) + i) = '|';
    }
    
    /* *************** */
    /* PRINT HISTOGRAM */
    /* *************** */
    
    // Print histogram vertically from top to bottom starting 4 spaces above max bin.
    // Prints in user-selected color theme.
    size = histogram.n - maxVal - 4;
    int printCount = 0;
    for(int i = size; i < histogram.n; i++){
        printf("    ");
        for(int j = 0; j < histogram.bins; j++){
            printCount++;
            
            // Print 10 bins in the first color of the chosen color theme.
            if(printCount <= 10){
                if(histogram.colorTheme == 1) printf(COLOR1 "%c", *(values + (i * histogram.bins) + j));
                else if(histogram.colorTheme == 2) printf(COLOR5 "%c", *(values + (i * histogram.bins) + j));
                else if(histogram.colorTheme == 3) printf(COLOR9 "%c", *(values + (i * histogram.bins) + j));
                else if(histogram.colorTheme == 4) printf(COLOR13 "%c", *(values + (i * histogram.bins) + j));
                else if(histogram.colorTheme == 5) printf(COLOR17 "%c", *(values + (i * histogram.bins) + j));
                else if(histogram.colorTheme == 6) printf(COLOR21 "%c", *(values + (i * histogram.bins) + j));
            }
            
            // Print the next 10 bins in the second color of the chosen color theme.
            else if(printCount > 10 && printCount <= 20){
                if(histogram.colorTheme == 1) printf(COLOR2 "%c", *(values + (i * histogram.bins) + j));
                else if(histogram.colorTheme == 2) printf(COLOR6 "%c", *(values + (i * histogram.bins) + j));
                else if(histogram.colorTheme == 3) printf(COLOR10 "%c", *(values + (i * histogram.bins) + j));
                else if(histogram.colorTheme == 4) printf(COLOR14 "%c", *(values + (i * histogram.bins) + j));
                else if(histogram.colorTheme == 5) printf(COLOR18 "%c", *(values + (i * histogram.bins) + j));
                else if(histogram.colorTheme == 6) printf(COLOR22 "%c", *(values + (i * histogram.bins) + j));
            }
            
            // Print the next 10 bins in the third color of the chosen color theme.
            else if(printCount > 20 && printCount <= 30){
                if(histogram.colorTheme == 1) printf(COLOR3 "%c", *(values + (i * histogram.bins) + j));
                else if(histogram.colorTheme == 2) printf(COLOR7 "%c", *(values + (i * histogram.bins) + j));
                else if(histogram.colorTheme == 3) printf(COLOR11 "%c", *(values + (i * histogram.bins) + j));
                else if(histogram.colorTheme == 4) printf(COLOR15 "%c", *(values + (i * histogram.bins) + j));
                else if(histogram.colorTheme == 5) printf(COLOR19 "%c", *(values + (i * histogram.bins) + j));
                else if(histogram.colorTheme == 6) printf(COLOR23 "%c", *(values + (i * histogram.bins) + j));
            }
            
            // Print the next 10 bins in the fourth color of the chosen color theme.
            else if(printCount > 30 && printCount <= 40){
                if(histogram.colorTheme == 1) printf(COLOR4 "%c", *(values + (i * histogram.bins) + j));
                else if(histogram.colorTheme == 2) printf(COLOR8 "%c", *(values + (i * histogram.bins) + j));
                else if(histogram.colorTheme == 3) printf(COLOR12 "%c", *(values + (i * histogram.bins) + j));
                else if(histogram.colorTheme == 4) printf(COLOR16 "%c", *(values + (i * histogram.bins) + j));
                else if(histogram.colorTheme == 5) printf(COLOR20 "%c", *(values + (i * histogram.bins) + j));
                else if(histogram.colorTheme == 6) printf(COLOR24 "%c", *(values + (i * histogram.bins) + j));
            }
            
            // Reset output color and printCount.
            printf(RESET);
            if(printCount >= 40 || j == histogram.bins-1) printCount = 0;
        }
        printf("\n");
    }
    
    // Inform user once more that colors change every 10 bins.
    printf("\n    * NOTE: COLORS CHANGE EVERY 10 BINS.");
    
    /* *********************** */
    /* PRINT USER-INPUT VALUES */
    /* *********************** */
    
    // Print user-input values for reference in the chosen color theme.
    printf("\n\n\t-----------");
    if(histogram.colorTheme == 1) printf(COLOR2 "\n\tSet Values: ");
    if(histogram.colorTheme == 2) printf(COLOR6 "\n\tSet Values: ");
    if(histogram.colorTheme == 3) printf(COLOR10 "\n\tSet Values: ");
    if(histogram.colorTheme == 4) printf(COLOR14 "\n\tSet Values: ");
    if(histogram.colorTheme == 5) printf(COLOR19 "\n\tSet Values: ");
    if(histogram.colorTheme == 6) printf(COLOR22 "\n\tSet Values: ");
    printf(RESET);
    printf("\n\t-----------\n");
    
    printf("\tn: %d\n", histogram.n);
    printf("\tm: %lf\n", histogram.m);
    printf("\tM: %lf\n", histogram.M);

    if(histogram.option == 2){
        printf("\tmu: %lf\n", histogram.mu);
        printf("\tsigma: %lf\n", histogram.sigma);
    }
    
    printf("\tbins: %d\n", histogram.bins);
    
    /* *********************************************** */
    /* CALCULATE AND PRINT POPULATION MEAN AND STD DEV */
    /* *********************************************** */
    
    // Calculate the population mean and std dev of all samples.
    // Display resutls in the chosen color theme.
    meanAndStdDev(histogram, samples);
    
    /* ********************* */
    /* PRINT BIN INFORMATION */
    /* ********************* */
    
    // Print the bin number that was used the most and how many times it was used.
    printf("\n\n\tBin [%d] with range", maxBin+1);
    printf(" [%lf, %lf]", ranges[maxBin][0], ranges[maxBin][1]);
    printf(" was used the most: %d times.\n", maxVal);
    
    // Inform user if the number of bins needed to be reduced in the chosen color theme.
    if(modified){
        if(histogram.colorTheme == 1) printf(COLOR3 "\n\n\t\e[5m(!)\e[0m");
        if(histogram.colorTheme == 2) printf(COLOR7 "\n\n\t\e[5m(!)\e[0m");
        if(histogram.colorTheme == 3) printf(COLOR11 "\n\n\t\e[5m(!)\e[0m");
        if(histogram.colorTheme == 4) printf(COLOR15 "\n\n\t\e[5m(!)\e[0m");
        if(histogram.colorTheme == 5) printf(COLOR20 "\n\n\t\e[5m(!)\e[0m");
        if(histogram.colorTheme == 6) printf(COLOR23 "\n\n\t\e[5m(!)\e[0m");
        printf(RESET);
        printf(" \e[4mATTENTION\e[0m: To acccommodate the bin width, the number");
        printf("of bins has been reduced to %d.\n", histogram.bins);
    }
    
    // Display the bin width used for setting the bin ranges in the chosen color theme.
    if(histogram.binWidth >= 1000.00){
        printf("\n\n\t---------------------------------");
        printf("-------------------------------\n");
    }
    
    else if(histogram.binWidth >= 100.00){
        printf("\n\n\t-------------------------------");
        printf("--------------------------------\n");
    }
    
    else if(histogram.binWidth >= 10.00){
        printf("\n\n\t--------------------------------");
        printf("------------------------------\n");
    }
    
    else{
        printf("\n\n\t-------------------------------");
        printf("------------------------------\n");
    }

    if(histogram.colorTheme == 1){
        printf(COLOR2 "\tRanges and number of values in each range.");
        printf(" Bin width: %.5f\n", histogram.binWidth);
    }
    
    if(histogram.colorTheme == 2){
        printf(COLOR8 "\tRanges and number of values in each range.");
        printf(" Bin width: %.5f\n", histogram.binWidth);
    }
    
    if(histogram.colorTheme == 3){
        printf(COLOR12 "\tRanges and number of values in each range.");
        printf(" Bin width: %.5f\n", histogram.binWidth);
    }
    
    if(histogram.colorTheme == 4){
        printf(COLOR16 "\tRanges and number of values in each range.");
        printf(" Bin width: %.5f\n", histogram.binWidth);
    }
    
    if(histogram.colorTheme == 5){
        printf(COLOR20 "\tRanges and number of values in each range.");
        printf(" Bin width: %.5f\n", histogram.binWidth);
    }
    
    if(histogram.colorTheme == 6){
        printf(COLOR24 "\tRanges and number of values in each range.");
        printf(" Bin width: %.5f\n", histogram.binWidth);
    }
    
    printf(RESET);

    if(histogram.binWidth >= 1000.00){
        printf("\t---------------------------------");
        printf("-------------------------------\n\t");
    }
    
    else if(histogram.binWidth >= 100.00){
        printf("\t-------------------------------");
        printf("--------------------------------\n\t");
    }
    
    else if(histogram.binWidth >= 10.00){
        printf("\t-------------------------------");
        printf("------------------------------\n\t");
    }
    
    else{
        printf("\t------------------------------");
        printf("-------------------------------\n\t");
    }

    /* *************************** */
    /* PRINT BIN RANGES AND VALUES */
    /* *************************** */
    
    // File thisRange holds each line of ranges printed to the console.
    // Used for determining spacing in output.
    FILE *thisRange;
    
    // Display all ranges used for the bins.
    for(int i = 0; i < histogram.bins; i++){

        // Print the current line.
        printf("%d: [%lf, %lf] = %d", (i+1), ranges[i][0], ranges[i][1], bins[i]);
        
        if(ranges[i][0] == histogram.M || ranges[i][1] == histogram.M) break;
        
        // Create a file to hold the current line.
        thisRange = fopen("thisRange.txt", "w");

        // If opening file for writing fails, exit(1).
        if(thisRange == NULL) exit(1);

        // Write the current line to the file.
        fprintf(thisRange, "%d: [%lf, %lf] = %d\n", (i+1), ranges[i][0], ranges[i][1], bins[i]);

        // Close file for writing.
        fclose(thisRange);
        
        // Open file for reading.
        thisRange = fopen("thisRange.txt", "r");
        
        // If opening file for reading fails, exit(1).
        if(thisRange == NULL) exit(1);
        
        // Get the number of characters in the current line.
        char c;
        int numChars = 0;
        while(c != EOF){
            c = fgetc(thisRange);
            if(c == '\n') break;
            else numChars++;
        }

        // Close file for reading.
        fclose(thisRange);

        // Remove the range file.
        remove("thisRange.txt");

        // Print a certain number of tabs depending on the length of the current line.
        int numSpaces = 0;
        if(numChars <= 19) numSpaces = 20;
        else if(numChars == 20) numSpaces = 19;
        else if(numChars == 21) numSpaces = 18;
        else if(numChars == 22) numSpaces = 17;
        else if(numChars == 23) numSpaces = 16;
        else if(numChars == 24) numSpaces = 15;
        else if(numChars == 25) numSpaces = 14;
        else if(numChars == 26) numSpaces = 13;
        else if(numChars == 27) numSpaces = 12;
        else if(numChars == 28) numSpaces = 11;
        else if(numChars == 29) numSpaces = 10;
        else if(numChars == 30) numSpaces = 9;
        else if(numChars == 31) numSpaces = 8;
        else if(numChars == 32) numSpaces = 7;
        else if(numChars == 33) numSpaces = 6;
        else if(numChars == 34) numSpaces = 5;
        else if(numChars == 35) numSpaces = 4;
        else if(numChars == 36) numSpaces = 3;
        else if(numChars == 37) numSpaces = 2;
        else if(numChars >= 38) numSpaces = 1;
        
        for(int k = 1; k <= numSpaces; k++) printf(" ");

        // Start the next 4 ranges on a new line.
        if((i > 0) && ((i+1) % 4 == 0)) printf("\n\t");
    }

// TODO
int totalVals = 0;
for(int i = 0; i < histogram.bins; i++) totalVals += bins[i];
printf("\n\n\tTOTAL VALUES IN BINS: %d\n", totalVals);
    
    /* *********** */
    /* FREE MEMORY */
    /* *********** */
    
    // Free memory used for bins[] and values[].
    free(bins);
    free(values);
}
