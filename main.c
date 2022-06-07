#include "Header.h"

/********************************************************************************
 *	main.c displays intro message, menu options, and exit message.				*
 *																				*
 *	@author Debra-Lee Speight													*
 ********************************************************************************/

int main(int argc, char** argv){
	int menuChoice = 0;

	displayIntro();

	// While menu choice does not equal 6 (where 6 = "CLOSE JOURNAL").
	while(menuChoice < 6) menuChoice = displayMainMenu();

	displayExit();
	return (EXIT_SUCCESS);
}

/**
 * Displays introduction.
 * @credit (journal ASCII art): [n.a.] @ https://www.asciiart.eu/books/books
 */
void displayIntro(){
	printf("\n\n    ############################\n");
	printf("    #    PASSWORD PROTECTED    #\n");
	printf("    #     PERSONAL JOURNAL     #\n");
	printf("    ############################\n");
	printf("\n\n\t(\\\n");
	printf("\t\\'\\\n");
	printf("\t \\'\\    __________  \n");
	printf("\t/ ' |  ()_________)\n");
	printf("\t\\ '/    \\ ~~~~~~~~ \\\n");
	printf("\t  \\      \\ ~~~~~~   \\\n");
	printf("\t (==)     \\__________\\\n");
	printf("\t (__)     ()__________)\n\n\n");
}

/**
 * Displays exit message.
 * @credit (paper ASCII art): [dc] @ https://www.asciiart.eu/art-and-design/borders
 */
void displayExit(){
	printf("\n\n\t  ______________\n");
	printf("\t /  \\           \\\n");
	printf("\t|   |            |\n");
	printf("\t \\_ |  UNTIL     |\n");
	printf("\t    |    NEXT    |\n");
	printf("\t    |      TIME  |\n");
	printf("\t    |            |\n");
	printf("\t    |   _________|___\n");
	printf("\t    |  /            /\n");
	printf("\t    \\_/____________/\n\n\n");
	printf("\n");
}