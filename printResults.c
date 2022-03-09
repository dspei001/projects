#include "Header.h"

/**
 * Calls functions to print histogram, user input values, population mean and std dev, 
 * bins used the most, whether number of bins was modified, and ranges of each bin.
 * @param histogram : Pointer to Histogram struct.
 */
void printResults(Histogram *histogram){

	printHistogram(histogram);
	printUserInputValues(histogram);
	printPopMeanAndStdDev(histogram);
	printMaxBins(histogram);
	printRangeHeader(histogram);
	printBinRangesAndValues(histogram);
}

/**
 * Prints vertical histogram.
 * @param histogram : Pointer to Histogram struct.
 */
void printHistogram(Histogram *histogram){

	// Find the max value in bins[] to minimize empty space above the histogram.
	// (starts 4 spaces above max bin).
	int maxVal = 0;
	for(int i = 0; i < histogram->numBins; i++){
		if(histogram->bins[i] >= maxVal) maxVal = histogram->bins[i];
	}
    int printLength = histogram->n - maxVal - 4;

	// For printing the next color in the color theme every 10 bins.
    int printCount = 0;
    for(int i = printLength; i < histogram->n; i++){
        printf("    ");
        for(int j = 0; j < histogram->numBins; j++){
            printCount++;
			int graphCharsIndex = (i * histogram->numBins) + j;
			char message[2] = {*(histogram->graphChars+graphCharsIndex), '\0'};

            // Change the color of the bin bars every 10 bins.
            if(printCount <= 10)
				applyColor(histogram->colorTheme, 1, message);
            else if(printCount > 10 && printCount <= 20)
				applyColor(histogram->colorTheme, 2, message);
            else if(printCount > 20 && printCount <= 30)
				applyColor(histogram->colorTheme, 3, message);
            else if(printCount > 30 && printCount <= 40)
				applyColor(histogram->colorTheme, 4, message);

            // Reset printCount.
            if(printCount >= 40 || j == histogram->numBins-1) printCount = 0;
        }
        printf("\n");
    }
    printf("\n    * NOTE: COLORS CHANGE EVERY 10 BINS.");
}

/**
 * Prints user input values: n (number of samples), lower and upper sample range,
 * mean and std dev (if applicable), and number of bins.
 * @param histogram : Pointer to Histogram struct.
 */
void printUserInputValues(Histogram *histogram){

    // Print user-input values for reference in the chosen color theme.
	printf("\n\n\t");
    for(int i = 0; i < 11; i++) printf("-");
	applyColor(histogram->colorTheme, 2, "\n\tSet Values: \n\t");
    for(int i = 0; i < 11; i++) printf("-");

    printf("\n\tn: %d\n", histogram->n);
    printf("\tm: %f\n", histogram->m);
    printf("\tM: %f\n", histogram->M);

    if(histogram->distribution == 2){
        printf("\tmu: %f\n", histogram->mu);
        printf("\tsigma: %f\n", histogram->sigma);
    }

    printf("\tbins: %d\n", histogram->numBins);
}

/**
 * Calculates and prints population mean and population std dev.
 * @param histogram : Pointer to Histogram struct.
 */
void printPopMeanAndStdDev(Histogram *histogram){

    double sum = 0.00;
    double popMean = 0.00;
    double popStdDev = 0.00;

    // Calculate the sum of all samples.
    for(int i = 0; i < histogram->n; i++) sum += histogram->samples[i];

    // Calculate the mean of all samples.
    popMean = sum / (double)histogram->n;

    // Calculate the standard deviation of all samples.
    for(int i = 0; i < histogram->n; i++) 
		popStdDev += (double)pow(histogram->samples[i] - popMean, 2.0);
    popStdDev = (double)sqrt(popStdDev / (histogram->n-1));

    // Print title in chosen color theme. 
    printf("\n\n\t");
	for(int i = 0; i < 27; i++) printf("-");
	applyColor(histogram->colorTheme, 1, "\n\tPopulation Mean and StdDev:\n\t");
    for(int i = 0; i < 27; i++) printf("-");

	// Print results.
    printf("\n\tPopulation Mean: %.5f\n", popMean);
    printf("\tPopulation Standard Deviation: %.5f\n", popStdDev);
}

/**
 * Prints the most-used bins and number of times they were used.
 * @param histogram : Pointer to Histogram struct.
 */
void printMaxBins(Histogram *histogram){

	// Find the most-used bins.
	int maxVal = 0;
	int maxBins[histogram->numBins];
	int maxBinsIndex = -1;
	for(int i = 0; i < histogram->numBins; i++){
		if(histogram->bins[i] >= maxVal){
	    	maxVal = histogram->bins[i];
			maxBinsIndex++;
			maxBins[maxBinsIndex] = i;
		}
	}

	// Print highest bin count. Formatting is dependent on number of digits in maxVal.
	int digitCount = getNumDigits(maxVal);
	printf("\n\n\t");
	for(int i = 0; i < (29+digitCount); i++) printf("-");
	char message[60] = {"\0"};
	sprintf(message, "\n\tBin(s) with Highest Count (%d):\n\t", maxVal);
	applyColor(histogram->colorTheme, 3, message);
	for(int i = 0; i < (29+digitCount); i++) printf("-");

	// Print the most-used bin number(s) and their ranges.
	for(int i = 0; i <= maxBinsIndex; i++){
		if(histogram->bins[maxBins[i]] == maxVal){
			printf("\n\tBin [%d] with range [%f, %f]", maxBins[i]+1,
											  *(histogram->ranges+(maxBins[i]*2)+0),
											  *(histogram->ranges+(maxBins[i]*2)+1));
		}
    }
	printf("\n");
}

/**
 * Prints a header for the list of bin ranges.
 * @param histogram : Pointer to Histogram struct.
 */
void printRangeHeader(Histogram *histogram){

	char message[150] = {"\0"};

	// Let user know if the number of bins has been modified.
	if(histogram->binsModified){
		sprintf(message, "\n\n\t\e[5m(!)\e[0m To accommodate bin width, "
				"the number of bins has been reduced to %d.\n", histogram->numBins);
		applyColor(histogram->colorTheme, 3, message);
	}

	// Formatting is dependent on number of digits in histogram->binWidth.
	int digitCount = getNumDigits(histogram->binWidth);
    printf("\n\n\t");
	for(int i = 0; i < (60+digitCount); i++) printf("-");
	strcpy(message, "\0");
	sprintf(message, "\n\tRanges and number of values in each range. Bin width: %.5f\n\t",
			histogram->binWidth);
	applyColor(histogram->colorTheme, 4, message);
    for(int i = 0; i < (60+digitCount); i++) printf("-");
	printf("\n\t");
}

/**
 * Prints the bin ranges and number of samples that fell into each bin.
 * @param histogram : Pointer to Histogram struct.
 */
void printBinRangesAndValues(Histogram *histogram){

    // Traverse histogram->numBins to print each range per bin.
    for(int i = 0; i < histogram->numBins; i++){
		char message[2000] = {"\0"};

		// Get the number of characters in the current line.
		int numChars =
			sprintf(message, "%d: [%f, %f] = %d", (i+1), *(histogram->ranges+(i*2)+0),
        								*(histogram->ranges+(i*2)+1), histogram->bins[i]);

		// Print the current line.
        printf("%s", message);

        // Print a certain number of spaces depending on the length of the current line.
        int numSpaces = setNumSpaces(numChars);
        for(int k = 1; k <= numSpaces; k++) printf(" ");

        // Start the next 4 ranges on a new line.
        if((i > 0) && ((i+1) % 4 == 0)) printf("\n\t");

		// If loop has reached upper sample range, break.
		if(*(histogram->ranges+(i*2)+0) == histogram->M
			|| *(histogram->ranges+(i*2)+1) == histogram->M) break;
    }
}