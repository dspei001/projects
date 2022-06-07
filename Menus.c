#include "Header.h"

/********************************************************************************
 *	Menus.c displays main and sub menus with input validation and redirects		*
 *	user to selected journal operations;										*
 *	NOTE: The functions in this class are listed in 2 groups,					*
 *		  "MENU FUNCTIONS" and "UTILITIES", where "MENU FUNCTIONS"				*
 *		  performs the expected operations based on the program menu,			*
 *		  and where "UTILITIES" functions assist the "MENU FUNCTIONS".			*
 *																				*
 *	@author Debra-Lee Speight													*
 ********************************************************************************/


/************************************************************/
/*                     MENU FUNCTIONS                       */
/************************************************************/

/**
 * Displays "MAIN" menu on loop with input validation;
 * if user chooses 6 on "MAIN" menu or 4 on any sub-menu
 * the program will close, and if user chooses 3 on any
 * sub-menu the program will return here to "MAIN" menu.
 * @return mainMenuChoice
 */
int displayMainMenu(){
	int mainMenuChoice = 0;
	printf("\n\n\t###################\n");
	printf("\t#    MAIN MENU    #\n");
	printf("\t###################\n");
	printf("\n\tADD\t\t[1]\n");
	printf("\tVIEW\t\t[2]\n");
	printf("\tEDIT\t\t[3]\n");
	printf("\tDELETE\t\t[4]\n");
	printf("\tRESET PASSWORD\t[5]\n");
	printf("\tCLOSE JOURNAL\t[6]\n");

	mainMenuChoice = ensureChoiceWithinBoundary(1, 6);
	if(mainMenuChoice == 1){
		if(displayAddMenuAndRedirect() == 4) return 6;
	}
	else if(mainMenuChoice == 2){
		if(displayViewMenuAndRedirect() == 4) return 6;
	}
	else if(mainMenuChoice == 3){
		if(displayEditMenuAndRedirect() == 4) return 6;
	}
	else if(mainMenuChoice == 4){
		if(displayDeleteMenuAndRedirect() == 4) return 6;
	}
	else if(mainMenuChoice == 5) resetPW();
	return mainMenuChoice;
}

/**
 * Displays "ADD" sub-menu on loop with input validation until the
 * option to go back to "MAIN" menu is selected (addMenuChoice = 3)
 * or the option to close journal is selected (addMenuChoice = 4).
 * @return addMenuChoice
 */
int displayAddMenuAndRedirect(){
	int addMenuChoice = 0, addCount = 0;
	char addAnother = 'y';
	do{
		addMenuChoice = 0;
		printf("\n\n\t************\n");
		printf("\t* ADD MENU *\n");
		printf("\t************\n");
		printf("\n\tAdd new entry\t\t[1]\n");
		printf("\tAdd to existing entry\t[2]\n");
		printf("\tBack to main menu\t[3]\n");
		printf("\tClose journal\t\t[4]\n");

		addMenuChoice = ensureChoiceWithinBoundary(1, 4);
		if(addMenuChoice == 1) addCount += addNewEntry();
		else if(addMenuChoice == 2) addCount += addToExisting();
		else if(addMenuChoice == 3 || addMenuChoice == 4) break;

		printf("\n\tAdd another? (Y/N)  ");
		scanf("%c", &addAnother);
		getc(stdin);
	}while(addAnother == 'y' || addAnother == 'Y');
	displayAddCount(addCount);
	return addMenuChoice;
}

/**
 * Displays "VIEW" sub-menu on loop with input validation until the
 * option to go back to "MAIN" menu is selected (viewMenuChoice = 3)
 * or the option to close journal is selected (viewMenuChoice = 4);
 * password validation occurs here.
 * @return viewMenuChoice
 */
int displayViewMenuAndRedirect(){
	int viewMenuChoice = 0;
	char viewAnother = 'y';
	if(validatePW()){
		do{
			viewMenuChoice = 0;
			printf("\n\n\t*************\n");
			printf("\t* VIEW MENU *\n");
			printf("\t*************\n");
			printf("\n\tView whole entry\t[1]\n");
			printf("\tView entry section\t[2]\n");
			printf("\tBack to main menu\t[3]\n");
			printf("\tClose journal\t\t[4]\n");

			viewMenuChoice = ensureChoiceWithinBoundary(1, 4);
			if(viewMenuChoice == 1) viewEntry();
			else if(viewMenuChoice == 2) viewSection();
			else if(viewMenuChoice == 3 || viewMenuChoice == 4) break;

			printf("\n\tView another? (Y/N)  ");
			scanf("%c", &viewAnother);
			getc(stdin);
		}while(viewAnother == 'y' || viewAnother == 'Y');
	}
	return viewMenuChoice;
}

/**
 * Displays "EDIT" sub-menu on loop with input validation until the
 * option to go back to "MAIN" menu is selected (editMenuChoice = 3)
 * or the option to close journal is selected (editMenuChoice = 4);
 * password validation occurs here.
 * @return editMenuChoice
 */
int displayEditMenuAndRedirect(){
	int editMenuChoice = 0, editCount = 0;
	char editAnother = 'y';
	if(validatePW()){
		do{
			editMenuChoice = 0;
			printf("\n\n\t*************\n");
			printf("\t* EDIT MENU *\n");
			printf("\t*************\n");
			printf("\n\tEdit whole section of entry\t[1]\n");
			printf("\tEdit one section field\t\t[2]\n");
			printf("\tBack to main menu\t\t[3]\n");
			printf("\tClose journal\t\t\t[4]\n");

			editMenuChoice = ensureChoiceWithinBoundary(1, 4);
			if(editMenuChoice == 1) editCount += editSection();
			else if(editMenuChoice == 2) editCount += editSectionField();
			else if(editMenuChoice == 3 || editMenuChoice == 4) break;

			printf("\n\tEdit another? (Y/N)  ");
			scanf("%c", &editAnother);
			getc(stdin);
		}while(editAnother == 'y' || editAnother == 'Y');
	}
	displayEditCount(editCount);
	return editMenuChoice;
}

/**
 * Displays "DELETE" sub-menu on loop with input validation until the
 * option to go back to "MAIN" menu is selected (deleteMenuChoice = 3)
 * or the option to close journal is selected (deleteMenuChoice = 4);
 * password validation occurs here.
 * @return deleteMenuChoice
 */
int displayDeleteMenuAndRedirect(){
	int deleteMenuChoice = 0, deleteCount = 0;
	char deleteAnother = 'y';
	if(validatePW()){
		do{
			deleteMenuChoice = 0;
			printf("\n\n\t***************\n");
			printf("\t* DELETE MENU *\n");
			printf("\t***************\n");
			printf("\n\tDelete whole entry\t[1]\n");
			printf("\tDelete entry section\t[2]\n");
			printf("\tBack to main menu\t[3]\n");
			printf("\tClose journal\t\t[4]\n");

			deleteMenuChoice = ensureChoiceWithinBoundary(1, 4);
if(deleteMenuChoice == 1) deleteCount += 1;//deleteEntry();
else if(deleteMenuChoice == 2) deleteCount += 1;//deleteSection();
			else if(deleteMenuChoice == 3 || deleteMenuChoice == 4) break;

			printf("\n\tDelete another? (Y/N)  ");
			scanf("%c", &deleteAnother);
			getc(stdin);
		}while(deleteAnother == 'y' || deleteAnother == 'Y');
	}
	displayDeleteCount(deleteCount);
	return deleteMenuChoice;
}


/************************************************************/
/*                        UTILITIES                         */
/************************************************************/

/**
 * Ensures menu choices are within the specified boundary.
 * @param lowerLimit
 * @param upperLimit
 * @return menuChoice
 */
int ensureChoiceWithinBoundary(int lowerLimit, int upperLimit){
	int menuChoice = 0;
	while(menuChoice < lowerLimit || menuChoice > upperLimit){
		printf("\n\tSELECT OPTION: \t");
		scanf("%d", &menuChoice);
		getc(stdin);
	}
	return menuChoice;
}

/**
 * Displays the number of successful adds performed.
 * @param addCount
 */
void displayAddCount(int addCount){
	if(addCount > 0){
		printf("\n\t(%d) SUCCESSFULLY CREATED SECTION", addCount);
		if(addCount > 1) printf("S");
		printf("\n");
	}
	else printf("\n\tNO SECTIONS CREATED\n");
}

/**
 * Displays the number of successful edits performed.
 * @param editCount
 */
void displayEditCount(int editCount){
	if(editCount > 0){
		printf("\n\t(%d) SUCCESSFUL EDIT", editCount);
		if(editCount > 1) printf("S");
		printf("\n");
	}
	else printf("\n\tNO EDITS PERFORMED\n");
}

/**
 * Displays the number of successful deletions performed.
 * @param deleteCount
 */
void displayDeleteCount(int deleteCount){
	if(deleteCount > 0){
		printf("\n\t(%d) SUCCESSFUL DELETION", deleteCount);
		if(deleteCount > 1) printf("S");
		printf("\n");
	}
	else printf("\n\tNO DELETIONS PERFORMED...\n");
}