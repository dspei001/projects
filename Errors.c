#include "Header.h"

/********************************************************************************
 *	Errors.c provides the appropriate message upon encountering various			*
 *	program errors.																*
 *																				*
 *	@author Debra-Lee Speight													*
 ********************************************************************************/

void fileCreationError(char *filename){
	printf("\n\t(!) FILE CREATION ERROR:");
	printf(" Error creating new file [%s].\n", filename);
	exit(1);
}

void fileReadingError(char *filename){
	printf("\n\t(!) FILE-READING ERROR:");
	printf(" Error reading from file [%s].\n", filename);
	exit(1);
}

void fileWritingError(char *filename){
	printf("\n\t(!) FILE-WRITING ERROR:");
	printf(" Error writing to file [%s].\n", filename);
	exit(1);
}

void nonexistentEntryError(char *entry){
	printf("\n\t(!) ERROR:");
	printf(" Entry [%s] does not exist.\n", entry);
}

void entryExistsError(char *entry){
	printf("\n\t(!) ERROR: Entry [%s] already exists.\n", entry);
}

void nonexistentSectionError(char *section, char *entry){
	printf("\n\t(!) ERROR: Section [%s]", section);
	printf(" does not exist in entry [%s].\n", entry);
}

void sectionExistsError(char *section, char *entry){
	printf("\n\t(!) ERROR: Section [%s] already exists", section);
	printf(" in entry [%s].\n", entry);
}

void PWfileAccessError(){
	printf("\n\t(!) FATAL ERROR:");
	printf(" ILLEGAL FILE ACCESS ATTEMPTED!\n");
	exit(1);
}

void defaultPWalert(){
	printf("\n\t(!) ALERT: Default password is currently set.");
	printf("\n\t           ");
	printf("Select RESET PASSWORD from main menu to change it.\n");
}