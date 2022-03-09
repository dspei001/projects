#include "Header.h"

/**
 * Gets the number of digits that would affect the number of dashes in a header.
 * @param valueForParsing : value for parsing number of digits.
 * @return digitCount
 */
int getNumDigits(int valueForParsing){

	int temp = valueForParsing;
	int digitCount = 0;
	do{
		temp /= 10;
		digitCount++;
	}while(temp != 0);

	return digitCount;
}

/**
 * Returns the number of spaces needed for printing.
 * @param numChars : Number of characters in a string.
 * @return numSpaces
 */
int setNumSpaces(int numChars){

	int numSpaces = 0;
	int numCharsCounter = 20;
	int numSpacesCounter = 19;
	if(numChars <= 19) numSpaces = 20;
	else if(numChars >= 38) numSpaces = 1;
	else{
		for(int i = 0; i < 20; i++){
			if(numChars == numCharsCounter) numSpaces = numSpacesCounter;
			numCharsCounter++;
			numSpacesCounter--;
		}
	}

	return numSpaces;
}

/**
 * Prints messages in the specified color scheme.
 * @param colorTheme : Code for color theme.
 * @param colorCode : Code for colors 1-4 of selected color theme.
 * @param message : String for which to apply color.
 */
void applyColor(int colorTheme, int colorCode, char* message){

	if(colorTheme == 1){
		if(colorCode == 1) printf(COLOR1 "%s", message);
		else if(colorCode == 2) printf(COLOR2 "%s", message);
		else if(colorCode == 3) printf(COLOR3 "%s", message);
		else if(colorCode == 4) printf(COLOR4 "%s", message);
	}
	else if(colorTheme == 2){
		if(colorCode == 1) printf(COLOR5 "%s", message);
		else if(colorCode == 2) printf(COLOR6 "%s", message);
		else if(colorCode == 3) printf(COLOR7 "%s", message);
		else if(colorCode == 4) printf(COLOR8 "%s", message);
	}
	else if(colorTheme == 3){
		if(colorCode == 1) printf(COLOR9 "%s", message);
		else if(colorCode == 2) printf(COLOR10 "%s", message);
		else if(colorCode == 3) printf(COLOR11 "%s", message);
		else if(colorCode == 4) printf(COLOR12 "%s", message);
	}
	else if(colorTheme == 4){
		if(colorCode == 1) printf(COLOR13 "%s", message);
		else if(colorCode == 2) printf(COLOR14 "%s", message);
		else if(colorCode == 3) printf(COLOR15 "%s", message);
		else if(colorCode == 4) printf(COLOR16 "%s", message);
	}
	else if(colorTheme == 5){
		if(colorCode == 1) printf(COLOR17 "%s", message);
		else if(colorCode == 2) printf(COLOR18 "%s", message);
		else if(colorCode == 3) printf(COLOR19 "%s", message);
		else if(colorCode == 4) printf(COLOR20 "%s", message);
	}
	else if(colorTheme == 6){
		if(colorCode == 1) printf(COLOR21 "%s", message);
		else if(colorCode == 2) printf(COLOR22 "%s", message);
		else if(colorCode == 3) printf(COLOR23 "%s", message);
		else if(colorCode == 4) printf(COLOR24 "%s", message);
	}
	printf(RESET);
}