#include "Header.h"

/********************************************************************************
 *	Password.c file contains password-related operations such as encrypting,	*
 *	decrypting, validating, and resetting the password file.					*
 *																				*
 *	@author Debra-Lee Speight													*
 ********************************************************************************/

/**
 * Allows user to reset password upon validation of current password;
 * continues asking for new password and confirmation of new password
 * until the two are a match.
 */
void resetPW(){
	char newPW[50] = "newPW";
	char confirmNewPW[50] = "confirmNewPW";
	bool oldPWvalidated = validatePW(), newPWvalidated = false;

	FILE *PWfile = fopen("PW", "w+");
	if(PWfile == NULL) fileCreationError("PASSWORD FILE");

	while(oldPWvalidated && !newPWvalidated){
		printf("\n\tEnter new password:  ");
		scanf("%s", newPW);

		printf("\tConfirm new password:  ");
		scanf("%s", confirmNewPW);

		if(strcmp(newPW, confirmNewPW) == 0){
			newPWvalidated = true;
			fputs(encryptPW(newPW), PWfile);
			fclose(PWfile);
			printf("\n\tPassword changed successfully.\n");
		}
		else printf("\n\t(!) ERROR: The passwords do not match.\n");
	}
}

/**
 * Validates the password by comparing the decrypted password to the user's
 * password input; user gets 3 attempts to enter the correct password.
 * @return true if password entered is correct; false otherwise
 */
bool validatePW(){
	char pwEntered[50];
	char *currentPW = (char*)calloc(50, sizeof(char));
	currentPW = getCurrentPW();
	decryptPW(currentPW);

	for(int i = 0; i < 3; i++){
		printf("\n\tENTER CURRENT PASSWORD:  ");
		scanf("%s", pwEntered);
		if(strcmp(pwEntered, currentPW) == 0){
			printf("\n\tACCESS GRANTED!\n");
			encryptPW(currentPW);
			return true;
		}
		else printf("\n\tINVALID PASSWORD\n");
	}
	printf("\n\tACCESS DENIED!\n");
	encryptPW(currentPW);
	return false;
}

/**
 * Opens the password file, and returns the password encrypted;
 * if no password file exists, a default password is set before returning it
 * (see setDefaultPW()).
 * @return currentPW (encrypted)
 */
const char * getCurrentPW(){
	FILE *fileRead = fopen("PW", "r");
	if(fileRead == NULL){
		fclose(fileRead);
		setDefaultPW();
		fileRead = fopen("PW", "r");
		if(fileRead == NULL) fileReadingError("PW");
	}
	static char currentPW[50];
	fgets(currentPW, 50, fileRead);
	if(currentPW[0] == '.' + 9) defaultPWalert();
	fclose(fileRead);
	return currentPW;
}

/**
 * Creates a new password file, encrypts the default password, and writes the
 * encrypted default password to the password file.
 */
void setDefaultPW(){
	FILE *fileWrite = fopen("PW", "w+");
	if(fileWrite == NULL) fileCreationError("PASSWORD FILE");
	char defPW[2] = ".";
	defPW[0] += 9;
	fputs(defPW, fileWrite);
	fclose(fileWrite);
}

/**
 * Encrypts the password in the password text file for security.
 * @param password (decrypted)
 * @return password (encrypted)
 */
const char * encryptPW(char *password){
	for(int i = 0; i < strlen(password); i++)
		if(password[i] != '\n' && password[i] != 32)
			password[i] += 9;
	return password;
}

/**
 * Decrypts the password in the password text file for validation.
 * @param password (encrypted)
 * @return password (decrypted)
 */
const char * decryptPW(char *password){
	for(int i = 0; i < strlen(password); i++)
		if(password[i] != '\n' && password[i] != 32)
			password[i] -= 9;
	return password;
}