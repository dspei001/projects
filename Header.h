#ifndef HEADER_H
#define HEADER_H

#ifdef __cplusplus
extern "C" {
#endif


/* ******** */
/* INCLUDES */
/* ******** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>


/* ******* */
/* STRUCTS */
/* ******* */

typedef struct Histogram{
	// Booleans
	bool binsModified;

	// Literals
    int colorTheme;
    int distribution;
    int numBins;
    double binWidth;
    double mu;
    double sigma;
    double m;
    double M;
    int n;

	// Arrays
	char *graphChars;
	int *bins;
	double *samples;
	double *ranges;
}Histogram;


/* **************************** */
/* FUNCTIONS: generateSamples.c */
/* **************************** */

// Sets range for sample generation and runs distribution method based on user input.
void generateSamples(Histogram *histogram);

// Generates histogram sample values using uniform distribution.
void uniformDistribution(Histogram *histogram, int range);

// Generates histogram sample values using normal distribution.
void normalDistribution(Histogram *histogram);


/* ************************* */
/* FUNCTIONS: writeSamples.c */
/* ************************* */

// Calls a function to write sample values to file depending on number of samples.
void writeSamples(Histogram *histogram);

// Writes all sample values to one text file.
void writeOneFile(Histogram *histogram);

// Writes all sample values to two text files; half on one, half on the other.
void writeTwoFiles(Histogram *histogram);


/* **************************** */
/* FUNCTIONS: createHistogram.c */
/* **************************** */

// Calls functions to set bin width, set ranges, mark bins, and set histogram structure.
void createHistogram(Histogram *histogram);

// Sets the width of each bin.
void setBinWidth(Histogram *histogram);

// Sets the range for each bin.
void setBinRanges(Histogram *histogram);

// Marks each used bin.
void markBins(Histogram *histogram);

// Saves a bar into histogram.graphChars if a value is in a bin, or a space if not.
void setHistogramStructure(Histogram *histogram);


/* ************************* */
/* FUNCTIONS: printResults.c */
/* ************************* */

// Calls functions to print histogram, user input values, population mean and std dev,
// bins used the most, whether number of bins was modified, and ranges of each bin.
void printResults(Histogram *histogram);

// Prints vertical histogram.
void printHistogram(Histogram *histogram);

// Prints user input values: n (number of samples), lower and upper sample range,
// mean and std dev (if applicable), and number of bins.
void printUserInputValues(Histogram *histogram);

// Calculates and prints population mean and population std dev.
void printPopMeanAndStdDev(Histogram *histogram);

// Prints the most-used bins and number of times they were used.
void printMaxBins(Histogram *histogram);

// Prints a header for the list of bin ranges.
void printRangeHeader(Histogram *histogram);

// Prints the bin ranges and number of samples that fell into each bin.
void printBinRangesAndValues(Histogram *histogram);


/* ********************** */
/* FUNCTIONS: utilities.c */
/* ********************** */

// Gets the number of digits that would affect the number of dashes in a header.
int getNumDigits(int valueForParsing);

// Returns the number of spaces needed for printing.
int setNumSpaces(int numChars);

// Prints messages in the specified color scheme.
void applyColor(int colorTheme, int colorCode, char* message);


/* *********** */
/* COLOR CODES */
/* *********** */

#define RESET "\e[0m"

// GREYSCALE THEME
#define COLOR1 "\033[38;5;241m"
#define COLOR2 "\033[38;5;245m"
#define COLOR3 "\033[38;5;249m"
#define COLOR4 "\033[38;5;256m"

// AUTUMN THEME
#define COLOR5 "\033[38;5;214m"
#define COLOR6 "\033[38;5;202m"
#define COLOR7 "\033[38;5;11m"
#define COLOR8 "\033[38;5;179m"

// OCEAN THEME
#define COLOR9 "\033[38;5;26m"
#define COLOR10 "\033[38;5;39m"
#define COLOR11 "\x1b[33m"
#define COLOR12 "\033[38;5;74m"

// FOREST THEME
#define COLOR13 "\033[38;5;41m"
#define COLOR14 "\033[38;5;71m"
#define COLOR15 "\033[38;5;64m"
#define COLOR16 "\033[38;5;58m"

// CANDYCANE THEME
#define COLOR17 "\033[38;5;1m"
#define COLOR18 "\033[38;5;256m"
#define COLOR19 "\033[38;5;165m"
#define COLOR20 "\033[38;5;5m"

// EGGPLANT THEME
#define COLOR21 "\033[38;5;90m"
#define COLOR22 "\033[38;5;93m"
#define COLOR23 "\033[38;5;99m"
#define COLOR24 "\033[38;5;138m"


#ifdef __cplusplus
}
#endif

#endif /* HEADER_H */