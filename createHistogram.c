#include "Header.h"

/**
 * Calls functions to set bin width, set ranges, mark bins, and set histogram structure.
 * @param histogram : Pointer to Histogram struct.
 */
void createHistogram(Histogram *histogram){

	setBinWidth(histogram);
	setBinRanges(histogram);
	markBins(histogram);
	setHistogramStructure(histogram);
}

/**
 * Sets the width of each bin.
 * @param histogram : Pointer to Histogram struct.
 */
void setBinWidth(Histogram *histogram){

	// Find range between the upper and lower sample value ranges.
	double sampleRange = histogram->M - histogram->m;
	if(sampleRange < 0) sampleRange *= -1;

	// Calculate the bin width using sampleRange.
	histogram->binWidth = sampleRange / (double)histogram->numBins;
	if(histogram->binWidth == 0.000000) histogram->binWidth = 0.000001;
}

/**
 * Sets the range for each bin.
 * @param histogram : Pointer to Histogram struct.
 */
void setBinRanges(Histogram *histogram){

    // For saving the ranges used for each bin.
	double ranges[histogram->numBins][2];

	// Find the minimum sample value and set it as the first value of the first range.
	ranges[0][0] = histogram->M;
    for(int i = 0; i < histogram->n; i++)
		if(histogram->samples[i] < ranges[0][0]) ranges[0][0] = histogram->samples[i];

    // The second value of the first range is the minimum sample value + bin width.
	ranges[0][1] = ranges[0][0] + histogram->binWidth;

    // Set the ranges for each bin using histogram->binWidth.
    for(int i = 1; i < histogram->numBins; i++){
		ranges[i][0] = ranges[i-1][1] + 0.000001;
		ranges[i][1] = ranges[i][0] + histogram->binWidth;

		// When loop has reached the last range, set manually and break.
        if(i == histogram->numBins-2){
			ranges[i+1][0] = ranges[i][1] + 0.000001;
			ranges[i+1][1] = histogram->M;
            break;
        }

		// If it is not possible to set all bin ranges with the calculated bin width,
		// histogram->numBins is modified.
		if(ranges[i][0] >= histogram->M){
			ranges[i][0] = histogram->M;
			ranges[i][1] = histogram->M;
            histogram->numBins = i + 1;
            histogram->binsModified = true;
			break;
        }		
		if(ranges[i][1] >= histogram->M){
			ranges[i][1] = histogram->M;
            histogram->numBins = i + 1;
            histogram->binsModified = true;
			break;
		}
    }

	// Copy ranges[][] to *ranges.
    histogram->ranges = (double*)malloc(histogram->numBins * 2 * sizeof(double));
	for(int i = 0; i < histogram->numBins; i++)
		for(int j = 0; j < 2; j++) *(histogram->ranges+(i*2)+j) = ranges[i][j];
}

/**
 * Marks each used bin.
 * @param histogram : Pointer to Histogram struct.
 */
void markBins(Histogram *histogram){

	// Holds the number of samples that fall into each bin.
    histogram->bins = (int*)calloc(histogram->numBins, sizeof(int));

    // Get each generated value from histogram->samples, and add to the appropriate bins.
    for(int i = 0; i < histogram->n; i++){
        for(int j = 0; j < histogram->numBins; j++){
			if((double)histogram->samples[i] >= *(histogram->ranges+(j*2)+0)
			&& (double)histogram->samples[i] <= *(histogram->ranges+(j*2)+1)){
				histogram->bins[j]++;
				break;
			}
        }
    }
}

/**
 * Saves a bar into histogram->graphChars if a value is in a bin, or a space if not.
 * @param histogram : Pointer to Histogram struct.
 */
void setHistogramStructure(Histogram *histogram){

    // Holds '|' if a bin was used or ' ' if not.
	histogram->graphChars = (char*)malloc(histogram->n * histogram->numBins * sizeof(char));

    // Determine when to save a space or a vertical bar.
    int printLength = 0;
    for(int i = 0; i < histogram->numBins; i++){
        printLength = (histogram->n - histogram->bins[i] - 1);

        for(int j = 0; j <= printLength; j++) 
			*(histogram->graphChars + (j * histogram->numBins) + i) = ' ';

        for(int k = (printLength+1); k < histogram->n; k++)
			*(histogram->graphChars + (k * histogram->numBins) + i) = '|';
    }
}