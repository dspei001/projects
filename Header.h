

/********************************************************************************
 *	Header.h contains all preprocessor directives, structs, and	function		*
 *	declarations separated by filename in comments.								*
 *																				*
 *	@author Debra-Lee Speight													*
 ********************************************************************************/

#ifndef HEADER_H
#define HEADER_H

#ifdef __cplusplus
extern "C" {
#endif

// unistd.h does not exist under Windows (VC); it is defined here:
// @credit: [Graeme Perrow] @ https://stackoverflow.com/a/230068
#ifdef WIN32
#include <io.h>
#define F_OK 0
#define access _access
#endif


/************/
/* INCLUDES */
/************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <unistd.h>


/***********/
/* STRUCTS */
/***********/

struct Entry{
	char time[31];
	char place[51];
    char mood[51];
	char entryBody[2001];
};

struct File{
	char *name;
};


/**********/
/* MAIN.C */
/**********/

void displayIntro();
void displayExit();


/***********/
/* MENUS.C */
/***********/

int displayMainMenu();
int displayAddMenuAndRedirect();
int displayViewMenuAndRedirect();
int displayEditMenuAndRedirect();
int displayDeleteMenuAndRedirect();

// MENUS UTILITIES:
int ensureChoiceWithinBoundary(int lowerLimit, int upperLimit);
void displayAddCount(int addCount);
void displayEditCount(int editCount);
void displayDeleteCount(int deleteCount);


/***********/
/* ENTRY.C */
/***********/

int addNewEntry();
int addToExisting();
bool viewEntry();
bool viewSection();
int editSection();
int editSectionField();
int deleteEntry();
int deleteSection();

// ENTRY UTILITIES:
void createSection();
void displayEntry();
void displaySection();
void printSectionFields();
bool editAllSectionFields();
const char * getFieldToEdit();
void editOneSectionField();
void editThisField(char *field, char *thisTime);
void writeSection(char *thisTime);
void writeAllSectionsExcept(char *time);
void renameFileToTemp();
bool confirmDeletion(char *deleteSectionMsg);
void getFilenameFromUser();
void getTimeFromUser(char *timePurpose);
void getPlaceFromUser();
void getMoodFromUser();
void getEntryBodyFromUser();
void validateTime();
bool entryExists();
bool sectionExists(char *thisSection);
const char * encryptEntry(char *entryData);
const char * decryptEntry(char *encryptedEntryData);


/**************/
/* PASSWORD.C */
/**************/

void resetPW();
bool validatePW();
const char * getCurrentPW();
void setDefaultPW();
const char * encryptPW(char *password);
const char * decryptPW(char *password);


/************/
/* ERRORS.C */
/************/

void fileCreationError(char *filename);
void fileReadingError(char *filename);
void fileWritingError(char *filename);
void nonexistentEntryError(char *entry);
void entryExistsError(char *entry);
void nonexistentSectionError(char *section, char *entry);
void sectionExistsError(char *section, char *entry);
void PWfileAccessError();
void defaultPWalert();


#ifdef __cplusplus
}
#endif

#endif /* HEADER_H */