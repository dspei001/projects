#ifndef Header_h
#define Header_h

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
    int colorTheme;
    int option;
    int bins;
    double binWidth;
    double mu;
    double sigma;
    double m;
    double M;
    int n;
}Histogram;

/* ********* */
/* FUNCTIONS */
/* ********* */

// Generates samples based on the user-selected method of sample generation.
void generateSamples(Histogram histogram, double *samples);

// Calculates the population mean and std dev and displays the results.
void meanAndStdDev(Histogram histogram, double *samples);

// Writes sample values to a text file (or screen if section is uncommented).
void writeSamples(Histogram histogram, double *samples);

// Prints a vertical histogram, most-used bin, bins, ranges for each bin, and number of
// samples that fell into each bin. Calls meanAndStdDev().
void createHistogram(Histogram histogram, double *samples);

/* ************ */
/* COLOR THEMES */
/* ************ */

#define RESET "\e[0m"

// GREYSCALE
#define COLOR1 "\033[38;5;241m"
#define COLOR2 "\033[38;5;245m"
#define COLOR3 "\033[38;5;249m"
#define COLOR4 "\033[38;5;256m"

// AUTUMN
#define COLOR5 "\033[38;5;214m"
#define COLOR6 "\033[38;5;202m"
#define COLOR7 "\033[38;5;11m"
#define COLOR8 "\033[38;5;179m"

// OCEAN
#define COLOR9 "\033[38;5;26m"
#define COLOR10 "\033[38;5;39m"
#define COLOR11 "\x1b[33m"
#define COLOR12 "\033[38;5;74m"

// FOREST
#define COLOR13 "\033[38;5;41m"
#define COLOR14 "\033[38;5;71m"
#define COLOR15 "\033[38;5;64m"
#define COLOR16 "\033[38;5;58m"

// CANDYCANE
#define COLOR17 "\033[38;5;1m"
#define COLOR18 "\033[38;5;256m"
#define COLOR19 "\033[38;5;165m"
#define COLOR20 "\033[38;5;5m"

// EGGPLANT
#define COLOR21 "\033[38;5;90m"
#define COLOR22 "\033[38;5;93m"
#define COLOR23 "\033[38;5;99m"
#define COLOR24 "\033[38;5;138m"

#endif /* Header_h */
