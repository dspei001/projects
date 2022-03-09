/*
@author: Debra-Lee Speight
*/

#include "Header.h"

/**
 * Test validity of certain user input values. Only digits, '.', and '-' are accepted.
 * @param userInput
 * @return true if valid user input; false otherwise.
 */
bool validateChoice(char* userInput){

	int length = strlen(userInput);
	int startingPoint = 0;

	// If first character is '-', start checking next character(s).
	if(userInput[0] == '-' && length > 1) startingPoint = 1;
	for(int i = startingPoint; i < length; i++){
		if(userInput[i] == '.') continue;
		if(!isdigit(userInput[i])) return false;
	}

	return true;
}

int main(int argc, char** argv){

    Histogram *histogram = (Histogram*)malloc(sizeof(Histogram));
    char userInput[100];

    /* ************ */
    /* INTRODUCTION */
    /* ************ */

    printf("\n\n\t***********************");
    printf("\n\t* HISTOGRAM GENERATOR *");
    printf("\n\t***********************");

    printf("\n\n\t        |");
    printf("\n\t        |  |");
    printf("\n\t        || ||");
    printf("\n\t       ||| ||");
    printf("\n\t       ||||||||");
    printf("\n\t      ||||||||||");
    printf("\n\t     |||||||||||||");
    printf("\n\n\t* NOTE: \e[3mThe output for this program is best viewed in");
    printf(" fullscreen mode.\e[0m");
    printf("\n\n\t----------------------------------------------");
    printf("\n\tSelect a method for sample value distribution:");
    printf("\n\t----------------------------------------------");

    /* *********************** */
    /* GET SAMPLE DISTRIBUTION */
    /* *********************** */

	// Do-while loop checks validity of user input.
    do{
        printf("\n\t1) Generate uniformly distributed integers in range [m, M].");
        printf("\n\t2) Generate normally distributed floats in range [m, M) ");
        printf("with mean, mu, and std dev, sigma.");
        printf("\n\t3) Exit.");
        printf("\n\n\tEnter selection: ");
        scanf(" %s", userInput);
		histogram->distribution = atoi(userInput);
    }while(histogram->distribution > 3 || histogram->distribution < 1);

    // If user selects option 3, exit program.
    if(histogram->distribution == 3){
        printf("\n\tEXITING HISTOGRAM GENERATOR ...\n");
        exit(0);
    }

    // Prompt user for number of samples, lower sample range, and upper sample range.
    printf("\n\t-------------------");
    printf("\n\tChoose your values:");
    printf("\n\t-------------------\n");

    /* ********************* */
    /* GET NUMBER OF SAMPLES */
    /* ********************* */

   	// Do-while loop checks validity of user input.
    do{
        printf("\tNumber of samples (n): ");
        scanf(" %s", userInput);
        histogram->n = atoi(userInput);
    }while(histogram->n <= 0);

    /* ********************** */
    /* GET LOWER SAMPLE RANGE */
    /* ********************** */

   	// Do-while loop checks validity of user input.
    do{
        printf("\tLower sample value range (m): ");
        scanf(" %s", userInput);
		histogram->m = atof(userInput);
    }while(!validateChoice(userInput));

    /* ********************** */
    /* GET UPPER SAMPLE RANGE */
    /* ********************** */

   	// Do-while loop checks validity of user input.
    do{
        printf("\tUpper sample value range (M): ");
        scanf(" %s", userInput);
        histogram->M = atof(userInput);
    }while(!validateChoice(userInput) || histogram->M <= histogram->m);

    // If user chooses option 2 for sample generation, get mean and std dev.
    if(histogram->distribution == 2){

        /* ******** */
        /* GET MEAN */
        /* ******** */

       	// Do-while loop checks validity of user input.
        do{
            printf("\tMean (mu): ");
            scanf(" %s", userInput);
            histogram->mu = atof(userInput);
        }while(!validateChoice(userInput));

        /* ********************** */
        /* GET STANDARD DEVIATION */
        /* ********************** */

       	// Do-while loop checks validity of user input.
        do{
            printf("\tStandard Deviation (sigma): ");
            scanf(" %s", userInput);
            histogram->sigma = atof(userInput);
        }while(!validateChoice(userInput));
    }

    /* ****************** */
    /* GET NUMBER OF BINS */
    /* ****************** */

	// Do-while loop checks validity of user input.
    // Max number of bins = 200. Anything over 200 will exceed a screen size of 15".
    do{
        printf("\n\tSelect the number of bins for the histogram.");
        printf("\n\tMaximum number of bins accepted is 200.\n\t");
        scanf(" %s", userInput);
        histogram->numBins = atoi(userInput);
    }while(histogram->numBins > 200 || histogram->numBins < 1);

    /* **************** */
    /* GET COLOR SCHEME */
    /* **************** */

    // Prompt user for histogram color scheme.
    printf("\n\t------------------------------");
    printf("\n\tSelect histogram color scheme:");
    printf("\n\t------------------------------\n");

	// Do-while loop checks validity of user input.
    do{
        printf("\t1) Greyscale:\t");
		applyColor(1, 1, "||||||||||");applyColor(1, 2, "||||||||||");
		applyColor(1, 3, "||||||||||");applyColor(1, 4, "||||||||||");

        printf("\n\t2) Autumn:\t");
		applyColor(2, 1, "||||||||||");applyColor(2, 2, "||||||||||");
		applyColor(2, 3, "||||||||||");applyColor(2, 4, "||||||||||");

        printf("\n\t3) Ocean:\t");
		applyColor(3, 1, "||||||||||");applyColor(3, 2, "||||||||||");
		applyColor(3, 3, "||||||||||");applyColor(3, 4, "||||||||||");

        printf("\n\t4) Forest:\t");
		applyColor(4, 1, "||||||||||");applyColor(4, 2, "||||||||||");
		applyColor(4, 3, "||||||||||");applyColor(4, 4, "||||||||||");

        printf("\n\t5) Candycane:\t");
		applyColor(5, 1, "||||||||||");applyColor(5, 2, "||||||||||");
		applyColor(5, 3, "||||||||||");applyColor(5, 4, "||||||||||");

        printf("\n\t6) Eggplant:\t");
		applyColor(6, 1, "||||||||||");applyColor(6, 2, "||||||||||");
		applyColor(6, 3, "||||||||||");applyColor(6, 4, "||||||||||");

        // Inform user that colors change every 10 bins.
        printf("\n\n\t* NOTE: COLORS CHANGE EVERY 10 BINS.");

        printf("\n\n\tEnter color theme selection: ");
        scanf(" %s", userInput);
        histogram->colorTheme = atoi(userInput);
    }while(histogram->colorTheme < 1 || histogram->colorTheme > 6);

	/* ************************** */
    /* GENERATE AND WRITE SAMPLES */
    /* ************************** */

    generateSamples(histogram);
    writeSamples(histogram);

	/* ************************** */
    /* GENERATE AND PRINT RESULTS */
    /* ************************** */

	createHistogram(histogram);
	printResults(histogram);

	// Direct user to the text file(s) that contains the sample values.
	printf("\n\n\t* SEE 'numbers");
	if(histogram->n <= 200000) printf(".txt' FOR SAMPLE VALUES.\n\n");
	else printf("1.txt' and 'numbers2.txt' FOR SAMPLE VALUES.\n\n");

int total = 0; for(int i = 0; i < histogram->numBins; i++) total+= histogram->bins[i]; printf("TOTAL IN BINS: %d", total);

	// Free all pointers and exit program.
	free(histogram->graphChars);
	free(histogram->bins);
	free(histogram->samples);
	free(histogram->ranges);
	free(histogram);

	return(0);
}