#include "Header.h"

/********************************************************************************
 *	Entry.c performs add, view, edit, delete, encrypt/decrypt, and various		*
 *	other operations on journal entry text files;								*
 * 	NOTE: The functions in this class are listed in 2 groups,					*
 *		  "MENU FUNCTIONS" and "UTILITIES", where "MENU FUNCTIONS"				*
 *		  performs the expected operations based on the program menu,			*
 *		  and where "UTILITIES" functions assist the "MENU FUNCTIONS".			*
 *																				*
 *	@author Debra-Lee Speight													*
 ********************************************************************************/

struct Entry entry;
struct File thisFile;


/************************************************************/
/*                     MENU FUNCTIONS                       */
/************************************************************/

/**
 * Creates and writes a new section to a newly created entry file.
 * @return 1 upon successful add; 0 otherwise (used for addCount in Menus)
 */
int addNewEntry(){
	getFilenameFromUser();
	if(entryExists()) entryExistsError(thisFile.name);
	else{
		FILE *file = fopen(thisFile.name, "w+");
		if(file == NULL) fileCreationError(thisFile.name);
		fclose(file);
		createSection();
		writeSection(entry.time);
		entry.time[strlen(entry.time)-1] = '\0';
		printf("\n\tSECTION [%s]", decryptEntry(entry.time));
		printf(" HAS BEEN ADDED TO [%s]\n", thisFile.name);
		return 1;
	}
	return 0;
}

/**
 * Creates and writes a new section to an existing entry file.
 * @return 1 upon successful add; 0 otherwise (used for addCount in Menus)
 */
int addToExisting(){
	getFilenameFromUser();
	if(entryExists()){
		createSection();
		writeSection(entry.time);
		entry.time[strlen(entry.time)-1] = '\0';
		printf("\n\tSECTION [%s]", decryptEntry(entry.time));
		printf(" HAS BEEN ADDED TO [%s]\n", thisFile.name);
		return 1;
	}
	else nonexistentEntryError(thisFile.name);
	return 0;
}

/**
 * Displays the entire user-specified entry file if it exists.
 * @return true if viewing entire entry is successful; false otherwise
 */
bool viewEntry(){
	getFilenameFromUser();
	if(entryExists()){
		displayEntry();
		return true;
	}
	else nonexistentEntryError(thisFile.name);
	return false;
}

/**
 * Displays only user-specified entry section if it exists.
 * @return true if viewing entry section is successful; false otherwise
 */
bool viewSection(){
	getFilenameFromUser();
	if(entryExists()){
		getTimeFromUser("VIEW");
		if(sectionExists(entry.time)){
			displaySection();
			return true;
		}
		else nonexistentSectionError(entry.time, thisFile.name);
	}
	else nonexistentEntryError(thisFile.name);
	return false;
}

/**
 * Edits a whole section of an entry file if it exists.
 * @return 1 upon successful edit; 0 otherwise (used for editCount in Menus)
 */
int editSection(){
	if(viewEntry()){
		getTimeFromUser("EDIT");
		if(sectionExists()){
			if(editAllSectionFields())
				if(remove(thisFile)) return 1;
		}
		else nonexistentSectionError(entry.time, thisFile.name);
	}
	return 0;
}

/**
 * Edits one section field of an entry file.
 * @return 1 upon successful edit; 0 otherwise (used for editCount in Menus)
 */
int editSectionField(){
	if(viewEntry()){
		getTimeFromUser("EDIT");
		if(sectionExists()){
			editOneSectionField();
			if(remove(thisFile)) return 1;
		}
		else nonexistentSectionError(entry.time, thisFile.name);
	}
	return 0;
}

/**
 * Deletes the entire user-specified entry file if it exists.
 * @return 1 upon successful deletion; 0 otherwise (used for deleteCount in Menus)
 */
int deleteEntry(){
//	if(viewEntry()){
//		if(confirmDeletion("")){
//			if(file.delete()){
//				printf("\n\t[%s] DELETED SUCCESSFULLY\n", thisFile.name);
//				return 1;
//			}
//		}
//	}
	return 0;
}

/**
 * Deletes only user-specified entry section if it exists.
 * @return 1 upon successful deletion; 0 otherwise (used for deleteCount in Menus)
 */
int deleteSection(){
//	if(viewEntry()){
//		getTimeFromUser("DELETE");
//		if(sectionExists()){
//			if(confirmDeletion(" section [" + time + "] for entry")){
//				renameFileToTemp();
//				writeAllSectionsExcept(time);
//				if(file.delete()){
//					printf("\n\tSECTION [%s] DELETED SUCCESSFULLY\n", time);
//					return 1;
//				}
//			}
//		}
//		else errors.errorMessage("section", thisFile.name, time);
//	}
	return 0;
}


/************************************************************/
/*                        UTILITIES                         */
/************************************************************/

/**
 * Creates a new entry section if it does not already exist.
 */
void createSection(){
	validateTime();
	getPlaceFromUser();
	getMoodFromUser();
	getEntryBodyFromUser();
}

/**
 * Displays an entire entry under a header.
 */
void displayEntry(){
	printf("\n\t------------------------------\n");
	printf("\tENTIRE ENTRY FOR [%s]: \n", thisFile.name);
	printf("\t------------------------------\n");

	char *line = NULL;
	size_t buff = 2000;
	FILE *file = fopen(thisFile.name, "r+");
	if(file == NULL) fileReadingError(thisFile.name);
	while(getline(&line, &buff, file) > 0){
		strncpy(entry.time, decryptEntry(line), 30);
		getline(&line, &buff, file);
		strncpy(entry.place, decryptEntry(line), 50);
		getline(&line, &buff, file);
		strncpy(entry.mood, decryptEntry(line), 50);
		getline(&line, &buff, file);
		strncpy(entry.entryBody, decryptEntry(line), 2000);
		line = NULL;
		printSectionFields();
	}
	fclose(file);
}

/**
 * Displays an entry section under a header.
 */
void displaySection(){
	printf("\n\t------------------------------------\n");
	printf("\tENTRY FOR [%s] AT [%s]:\n", thisFile.name, entry.time);
	printf("\t------------------------------------\n");

	char *line = NULL;
	size_t buff = 2000;
	FILE *file = fopen(thisFile.name, "r+");
	if(file == NULL) fileReadingError(thisFile.name);
	while(getline(&line, &buff, file) > 0){
		decryptEntry(line);
		if(line[strlen(line)-1] == '\n') line[strlen(line)-1] = '\0';
		if(strcmp(line, entry.time) == 0){
			strncat(entry.time, "\n", sizeof(char));
			getline(&line, &buff, file);
			strncpy(entry.place, decryptEntry(line), 50);
			getline(&line, &buff, file);
			strncpy(entry.mood, decryptEntry(line), 50);
			getline(&line, &buff, file);
			strncpy(entry.entryBody, decryptEntry(line), 2000);
			printSectionFields();
			fclose(file);
		}
		else for(int i = 0; i < 3; i++) getline(&line, &buff, file);
	}
	fclose(file);
}

/**
 * Prints all section fields.
 */
void printSectionFields(){
	printf("\n\tTIME: %s", entry.time);
	printf("\tPLACE: %s", entry.place);
	printf("\tMOOD: %s", entry.mood);
	printf("\tENTRY: "); // Formatted below for better viewing.
	int index = 0, charsPrinted = 0, length = strlen(entry.entryBody);
	while(index != length){
		char thisChar = entry.entryBody[index];
		printf("%c", thisChar);
		charsPrinted++;

		if(charsPrinted >= 63 && thisChar == ' '){
			printf("\n\t\t");
			charsPrinted = 0;
		}
		index++;
	}
}

/**
 * Allows user to change all section fields and rewrites the entry.
 * @return modified : true if section modified; false otherwise
 */
bool editAllSectionFields(){
	bool modified = false;
	char *line = NULL;
	size_t buff = 2000;
	FILE *file = fopen(thisFile.name, "r+");
	if(file == NULL) fileReadingError(thisFile.name);
renameFileToTemp();

	printf("\n\t[NOW EDITING ENTRY]\n");
	while(getline(&line, &buff, file) > 0){
		decryptEntry(line);
		if(line[strlen(line)-1] == '\n') line[strlen(line)-1] = '\0';
		if(strcmp(entry.time, line) == 0){
			createSection();
			writeSection(line);
			modified = true;
			printf("\n\t[%s] MODIFIED SUCCESSFULLY\n", thisFile.name);
		}
		else for(int i = 0; i < 3; i++) getline(&line, &buff, file);
	}
	fclose(file);
	return modified;
}

/**
 * Gets the specific field for editing from user.
 * @return a String designating the field to edit
 */
const char * getFieldToEdit(){
//	int editChoice = 0;
//	printf("\n\tSelect the section to edit:");
//	printf("\n\tEdit TIME\t[1]\n\tEdit PLACE\t[2]");
//	printf("\n\tEdit MOOD\t[3]\n\tEdit ENTRY\t[4]\n");
//
//	while(editChoice < 49 || editChoice > 52){
//		printf("\n\tSELECT OPTION: \t");
//		try{editChoice = in.nextLine().charAt(0);}
//		catch(StringIndexOutOfBoundsException e){}
//	}
//	if(editChoice == 49) return "TIME";
//	else if(editChoice == 50) return "PLACE";
//	else if(editChoice == 51) return "MOOD";
//	else if(editChoice == 52) return "ENTRY";
//	else return null;
return ""; // DELETE THIS !!
}

/**
 * Allows user to change one section field and rewrites the entry.
 */
void editOneSectionField(){
//	String field = getFieldToEdit();
//	String holdTime = time;
//	renameFileToTemp();
//	try{fileScan = new Scanner(file);}
//	catch(IOException e){errors.errorMessage("scanner", "", "");}
//	while(fileScan.hasNext()){
//		String thisTime = decryptEntry(fileScan.nextLine());
//		if(thisTime.equals(holdTime)){
//			editThisField(field, thisTime);
//			printf("\n\t[%s] MODIFIED SUCCESSFULLY\n", thisFile.name);
//		}
//		else{
//			place = decryptEntry(fileScan.nextLine());
//			mood = decryptEntry(fileScan.nextLine());
//			entryBody = decryptEntry(fileScan.nextLine());
//		}
//
//		if(thisTime.equals(holdTime) && field.equals("TIME")) writeSection(time);
//		else writeSection(thisTime);
//	}
//	fileScan.reset();
}

/**
 * Edits one field of an entry section given the specified field.
 * @param field
 * @param thisTime : used if specifying the time field
 */
void editThisField(char *field, char *thisTime){
//	printf("\n\t[NOW EDITING ENTRY]\n");
//	if(field.equals("TIME")){
//		validateTime();
//		place = decryptEntry(fileScan.nextLine());
//		mood = decryptEntry(fileScan.nextLine());
//		entryBody = decryptEntry(fileScan.nextLine());
//	}
//	else if(field.equals("PLACE")){
//		time = thisTime;
//		getPlaceFromUser();
//		fileScan.nextLine();
//		mood = decryptEntry(fileScan.nextLine());
//		entryBody = decryptEntry(fileScan.nextLine());
//	}
//	else if(field.equals("MOOD")){
//		time = thisTime;
//		place = decryptEntry(fileScan.nextLine());
//		getMoodFromUser();
//		fileScan.nextLine();
//		entryBody = decryptEntry(fileScan.nextLine());
//	}
//	else if(field.equals("ENTRY")){
//		time = thisTime;
//		place = decryptEntry(fileScan.nextLine());
//		mood = decryptEntry(fileScan.nextLine());
//		getEntryBodyFromUser();
//		fileScan.nextLine();
//	}
}

/**
 * Writes a given time section to an entry file after encrypting.
 * @param thisTime : time section to write
 */
void writeSection(char *thisTime){
	FILE *file = fopen(thisFile.name, "a+");
	if(file == NULL) fileWritingError(thisFile.name);
	sprintf(thisTime, "%s\n", encryptEntry(thisTime));
	sprintf(entry.place, "%s\n", encryptEntry(entry.place));
	sprintf(entry.mood, "%s\n", encryptEntry(entry.mood));
	sprintf(entry.entryBody, "%s\n", encryptEntry(entry.entryBody));
	fputs(thisTime, file);
	fputs(entry.place, file);
	fputs(entry.mood, file);
	fputs(entry.entryBody, file);
	fclose(file);
}

/**
 * Writes all but one section of an entry to a new file.
 * @param time : the section to skip
 */
void writeAllSectionsExcept(char *time){
//	try{fileScan = new Scanner(file);}
//	catch(IOException e){errors.errorMessage("scanner", "", "");}
//	while(fileScan.hasNext()){
//		String thisTime = decryptEntry(fileScan.nextLine());
//		place = decryptEntry(fileScan.nextLine());
//		mood = decryptEntry(fileScan.nextLine());
//		entryBody = decryptEntry(fileScan.nextLine());
//
//		if(!thisTime.equals(time)) writeSection(thisTime);
//	}
//	fileScan.reset();
}

/**
 * Renames file to "temp" for entry modifications and deletions.
 */
void renameFileToTemp(){
	FILE *temp = fopen("temp", "r+");

	file.renameTo(temp);
	file = new File("temp");
}

/**
 * Asks user to confirm the deletion of a section (if specified) or entire entry.
 * @param deleteSectionMsg : given message about section to delete, if specified
 * @return true if deletion confirmed by user; false otherwise
 */
bool confirmDeletion(char *deleteSectionMsg){
//	int confirm = 0;
//	do{
//		printf("\n\t(!) ALERT: DELETIONS CANNOT BE UNDONE\n");
//		printf("\tAre you sure you would like to delete" + deleteSectionMsg);
//		printf(" [" + thisFile.name + "]? (Y/N):   ");
//		try{confirm = in.nextLine().charAt(0);}
//		catch(StringIndexOutOfBoundsException e){confirm = 0;}
//	}while(confirm != 'y' && confirm != 'Y' && confirm != 'n' && confirm != 'N');
//	return (confirm == 'y' || confirm == 'Y');
return false;//DELETE THIS !!!
}

/**
 * Prompts user for entry filename; prevents password file access.
 */
void getFilenameFromUser(){
	thisFile.name = (char*)malloc(31);
	char filenameTemp[30] = "pw";
	while(strcmp(filenameTemp, "pw") == 0){
		printf("\n\tENTER ENTRY FILENAME AS DATE [mm-dd-yyyy]:   ");
		fflush(stdin);
		fgets(thisFile.name, 30, stdin);
		if(thisFile.name[strlen(thisFile.name)-1] == '\n') 
			thisFile.name[strlen(thisFile.name)-1] = '\0';

		for(int i = 0; i < strlen(thisFile.name); i++)
			filenameTemp[i] = tolower(thisFile.name[i]);

		if(strcmp(filenameTemp, "pw") == 0) PWfileAccessError();
	}
	if(strcmp(thisFile.name, "") == 0) strncpy(thisFile.name, " ", sizeof(char));
}

/**
 * Gets only the TIME field from the user.
 * @param timePurpose : the purpose for which time is being asked
 *						(add/view/edit/delete)
 */
void getTimeFromUser(char *timePurpose){
	printf("\n\tENTER TIME TO %s AS [hh:mm]am/pm:   ", timePurpose);
	fflush(stdin);
	fgets(entry.time, 30, stdin);
	if(entry.time[strlen(entry.time)-1] == '\n') 
		entry.time[strlen(entry.time)-1] = '\0';
	if(strcmp(entry.time, "") == 0) strncpy(entry.time, " ", sizeof(char));
}

/**
 * Gets only the PLACE field from the user.
 */
void getPlaceFromUser(){
	printf("\tWHERE ARE YOU?   ");
	fflush(stdin);
	fgets(entry.place, 50, stdin);
	if(entry.place[strlen(entry.place)-1] == '\n') 
		entry.place[strlen(entry.place)-1] = '\0';
	if(strcmp(entry.place, "") == 0) strncpy(entry.place, " ", sizeof(char));
}

/**
 * Gets only the MOOD field from the user.
 */
void getMoodFromUser(){
	printf("\tHOW ARE YOU FEELING?   ");
	fflush(stdin);
	fgets(entry.mood, 50, stdin);
	if(entry.mood[strlen(entry.mood)-1] == '\n') 
		entry.mood[strlen(entry.mood)-1] = '\0';
	if(strcmp(entry.mood, "") == 0) strncpy(entry.mood, " ", sizeof(char));
}

/**
 * Gets only the ENTRY field (entryBody) from the user.
 */
void getEntryBodyFromUser(){
	printf("\tENTRY:   ");
	fflush(stdin);
	fgets(entry.entryBody, 2000, stdin);
	if(entry.entryBody[strlen(entry.entryBody)-1] == '\n') 
		entry.entryBody[strlen(entry.entryBody)-1] = '\0';
	if(strcmp(entry.entryBody, "") == 0) strncpy(entry.entryBody, " ", sizeof(char));
}

/**
 * Prevents user from adding a time section that already exists.
 */
void validateTime(){
	bool exists = false;
	do{
		getTimeFromUser("ADD");
		char timeTemp[31] = "\0";
		strncpy(timeTemp, entry.time, strlen(entry.time));
		exists = sectionExists(timeTemp);
		if(exists) sectionExistsError(entry.time, thisFile.name);
	}while(exists);
}

/**
 * Determines if user-specified entry already exists
 * (prevents password file access).
 * @return true if entry exists; false otherwise
 */
bool entryExists(){
	if(access(thisFile.name, F_OK) == 0) return true;
	return false;
}

/**
 * Determines if user-specified time section of an entry already exists.
 * @return true if section exists; false otherwise
 */
bool sectionExists(char *thisSection){
	char *line = NULL;
	size_t buff = 2000;
	FILE *file = fopen(thisFile.name, "r+");
	if(file == NULL) fileReadingError(thisFile.name);

	while(getline(&line, &buff, file) > 0){
		if(line[strlen(line)-1] == '\n') line[strlen(line)-1] = '\0';
		if(strcmp(decryptEntry(line), thisSection) == 0){
			fclose(file);
			return true;
		}
		else for(int i = 0; i < 3; i++) getline(&line, &buff, file);
	}
	fclose(file);
	return false;
}

/**
 * Encrypts entry fields before adding to an entry file for security.
 * @param entryData (decrypted)
 * @return entryData (encrypted)
 */
const char * encryptEntry(char *entryData){
	for(int i = 0; i < strlen(entryData); i++)
		if(entryData[i] != '\n' && entryData[i] != 32)
			entryData[i] += 12;
	return entryData;	
}

/**
 * Decrypts entry fields from an entry file for viewing.
 * @param entryData (encrypted)
 * @return entryData (decrypted)
 */
const char * decryptEntry(char *entryData){
	for(int i = 0; i < strlen(entryData); i++)
		if(entryData[i] != '\n' && entryData[i] != 32)
			entryData[i] -= 12;
	return entryData;	
}