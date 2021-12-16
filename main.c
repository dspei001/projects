/*
Author: Debra-Lee Speight
Description: Histogram
            This program generates a vertical histogram based on sample values
            generated using the method of random value generation selected by the user.
            User is then prompted for the appropriate values for mean, standard
            deviation, and number of bins. The result is the histogram, sample mean,
            sample standard deviation, values entered by the user, the most-used bin,
            ranges for each bin, and number of values that fell into each bin.
 
            NOTE: All sample values are written to a text file for reference.
                  See printValues().
            NOTE: The Make option, 'make clean', will delete object files AND the
                  sample text file.
*/

#include "Header.h"

int main(int argc, char* argv[]){
    
    // Declare Histogram struct.
    Histogram histogram;

    // Double array pointer, samples, is used to hold the generated sample numbers.
    double *samples;
    
    // String, testValues, is used for user input validation.
    char *testValues = (char*)malloc(100 * sizeof(char));
    
    // Boolean, valid, is used to determine validity of user input.
    bool valid = true;

    /* ************ */
    /* INTRODUCTION */
    /* ************ */
    
    // Display intro.
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
    
    // Prompt user to select a method for sample value generation.
    printf("\n\n\t--------------------------------------------");
    printf("\n\tSelect a method for sample value generation:");
    printf("\n\t--------------------------------------------");
    
    /* ******************************* */
    /* GET METHOD OF SAMPLE GENERATION */
    /* ******************************* */
    
    // Test user input validity of sample generation option with a do-while loop.
    char testChoice = ' ';
    do{
        printf("\n\t1) Generate uniformly distributed integers in range [m, M].");
        printf("\n\t2) Generate normally distributed floats in range [m, M] ");
        printf("with mean, mu, and std dev, sigma.");
        printf("\n\t3) Exit.");
        printf("\n\n\tEnter selection: ");
        scanf(" %c", &testChoice);
    }while(testChoice < 49 || testChoice > 51);
    
    // Set the option as an integer based on the ASCII value of testChoice.
    histogram.option = testChoice - 48;
    
    // If user selects option 3, exit program.
    if(histogram.option == 3){
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
    
    // Test user input validity of number of samples with a do-while loop.
    do{
        printf("\tNumber of samples (n): ");
        scanf(" %s", testValues);
        histogram.n = atoi(testValues);
        for(int i = 0; i < strlen(testValues); i++){
            if(!isdigit(testValues[i])){
                valid = false;
                break;
            }
            else valid = true;
        }
    }while(histogram.n <= 0 || !valid);
    
    // Reset valid.
    valid = false;
    
    /* ********************** */
    /* GET LOWER SAMPLE RANGE */
    /* ********************** */
    
    // Test user input validity of lower sample range with a do-while loop.
    do{
        printf("\tLower sample value range (m): ");
        scanf(" %s", testValues);
        histogram.m = atof(testValues);
        for(int i = 0; i < strlen(testValues); i++){
            if(isalpha(testValues[i])){
                valid = false;
                break;
            }
            
            else valid = true;
        }
    }while(!valid);
    
    // Reset valid.
    valid = false;
    
    /* ********************** */
    /* GET UPPER SAMPLE RANGE */
    /* ********************** */
    
    // Test user input validity of upper sample range with a do-while loop.
    do{
        printf("\tUpper sample value range (M): ");
        scanf(" %s", testValues);
        histogram.M = atof(testValues);
        for(int i = 0; i < strlen(testValues); i++){
            if(isalpha(testValues[i])){
                valid = false;
                break;
            }
            
            else valid = true;
        }
    }while(!valid || histogram.M <= histogram.m);
    
    // Reset valid.
    valid = false;
    
    // If user chooses option 2 for sample generation, prompt for mean and std dev.
    if(histogram.option == 2){
        
        /* ******** */
        /* GET MEAN */
        /* ******** */
        
        // Test user input validity of the mean with a do-while loop.
        do{
            printf("\tMean (mu): ");
            scanf(" %s", testValues);
            histogram.mu = atof(testValues);
            for(int i = 0; i < strlen(testValues); i++){
                if(isalpha(testValues[i])){
                    valid = false;
                    break;
                }
                
                else valid = true;
            }
        }while(!valid);
        
        // Reset valid.
        valid = false;
        
        /* ********************** */
        /* GET STANDARD DEVIATION */
        /* ********************** */
        
        // Test user input validity of the std dev with a do-while loop.
        do{
            printf("\tStandard Deviation (sigma): ");
            scanf(" %s", testValues);
            histogram.sigma = atof(testValues);
            for(int i = 0; i < strlen(testValues); i++){
                if(isalpha(testValues[i])){
                    valid = false;
                    break;
                }
                
                else valid = true;
            }
        }while(!valid);
    }
    
    // Reset valid.
    valid = false;
    
    /* ****************** */
    /* GET NUMBER OF BINS */
    /* ****************** */
    
    // Test user input validity of the number of bins with a do-while loop.
    // Max number of bins = 200. Anything over 200 will exceed a screen size of 15".
    do{
        printf("\n\tSelect the number of bins for the histogram.");
        printf("\n\tMaximum number of bins accepted is 200.\n\t");
        scanf(" %s", testValues);
        histogram.bins = atoi(testValues);
        
        if(histogram.bins <= 200){
            for(int i = 0; i < strlen(testValues); i++){
                if(isalpha(testValues[i])){
                    valid = false;
                    break;
                }
                
                else valid = true;
            }
        }
    }while(!valid || histogram.bins > 200 || histogram.bins < 1);
    
    // Reset valid.
    valid = false;
    
    /* **************** */
    /* GET COLOR SCHEME */
    /* **************** */
    
    // Prompt user for histogram color scheme.
    printf("\n\t------------------------------");
    printf("\n\tSelect histogram color scheme:");
    printf("\n\t------------------------------\n");
    
    // Test user input validity of the histogram color scheme with a do-while loop.
    do{
        printf("\t1) Greyscale:\t");
        for(int i = 1; i <= 10; i++) printf(COLOR1 "|"); printf(RESET);
        for(int i = 1; i <= 10; i++) printf(COLOR2 "|"); printf(RESET);
        for(int i = 1; i <= 10; i++) printf(COLOR3 "|"); printf(RESET);
        for(int i = 1; i <= 10; i++) printf(COLOR4 "|"); printf(RESET);
        
        printf("\n\t2) Autumn:\t");
        for(int i = 1; i <= 10; i++) printf(COLOR5 "|"); printf(RESET);
        for(int i = 1; i <= 10; i++) printf(COLOR6 "|"); printf(RESET);
        for(int i = 1; i <= 10; i++) printf(COLOR7 "|"); printf(RESET);
        for(int i = 1; i <= 10; i++) printf(COLOR8 "|"); printf(RESET);

        printf("\n\t3) Ocean:\t");
        for(int i = 1; i <= 10; i++) printf(COLOR9 "|"); printf(RESET);
        for(int i = 1; i <= 10; i++) printf(COLOR10 "|"); printf(RESET);
        for(int i = 1; i <= 10; i++) printf(COLOR11 "|"); printf(RESET);
        for(int i = 1; i <= 10; i++) printf(COLOR12 "|"); printf(RESET);

        printf("\n\t4) Forest:\t");
        for(int i = 1; i <= 10; i++) printf(COLOR13 "|"); printf(RESET);
        for(int i = 1; i <= 10; i++) printf(COLOR14 "|"); printf(RESET);
        for(int i = 1; i <= 10; i++) printf(COLOR15 "|"); printf(RESET);
        for(int i = 1; i <= 10; i++) printf(COLOR16 "|"); printf(RESET);
        
        printf("\n\t5) Candycane:\t");
        for(int i = 1; i <= 10; i++) printf(COLOR17 "|"); printf(RESET);
        for(int i = 1; i <= 10; i++) printf(COLOR18 "|"); printf(RESET);
        for(int i = 1; i <= 10; i++) printf(COLOR19 "|"); printf(RESET);
        for(int i = 1; i <= 10; i++) printf(COLOR20 "|"); printf(RESET);
        
        printf("\n\t6) Eggplant:\t");
        for(int i = 1; i <= 10; i++) printf(COLOR21 "|"); printf(RESET);
        for(int i = 1; i <= 10; i++) printf(COLOR22 "|"); printf(RESET);
        for(int i = 1; i <= 10; i++) printf(COLOR23 "|"); printf(RESET);
        for(int i = 1; i <= 10; i++) printf(COLOR24 "|"); printf(RESET);
        
        // Inform user that colors change every 10 bins.
        printf("\n\n\t* NOTE: COLORS CHANGE EVERY 10 BINS.");
        
        printf("\n\n\tEnter color theme selection: ");
        scanf(" %s", testValues);
        histogram.colorTheme = atoi(testValues);
        
        for(int i = 0; i < strlen(testValues); i++){
            if(isalpha(testValues[i])){
                valid = false;
                break;
            }
            
            else valid = true;
        }
    }while(histogram.colorTheme < 1 || histogram.colorTheme > 6 || !valid);
    
    /* **************** */
    /* POPULATE SAMPLES */
    /* **************** */
    
    // Set the size of samples[].
    samples = (double*)malloc(histogram.n * sizeof(double));

    // Generate samples for samples[].
    generateSamples(histogram, samples);
    
    // Writes sample values to a text file (or STDOUT if section is uncommented).
    writeSamples(histogram, samples);
    
    /* **************** */
    /* CREATE HISTOGRAM */
    /* **************** */
    
    // Print the histogram. createHistogram() calls meanAndStdDev().
    createHistogram(histogram, samples);
    
    // Direct user to the text file that contains the sample values.
    printf("\n\n\t* NOTE: SEE 'numbers.txt' FOR SAMPLE VALUES.\n\n");
    
    /* *********** */
    /* FREE MEMORY */
    /* *********** */
    
    // Free memory allocated to samples[] testValues.
    free(testValues);
    free(samples);
    
    // Exit program.
    return 0;
}
