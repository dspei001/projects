
/*
 TODO:
    - Add help menu per subsection
    - Change section names?
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

// Structs.
struct record
{
    char time[10];
    char name[30];
    char place[30];
    char duration[30];
    char note[1500];
} ;

// Functions.
int password();
void addrecord();
void viewrecord();
void editrecord();
void editpassword();
void deleterecord();
void encrypt(char *data);
void decrypt(char *data);
void fileErrorMessage(char *type);

int main(){
    int menuChoice = 0;

    // Introduction.
    printf("\n\n\t***************************************\n");
    printf("\t* PASSWORD PROTECTED PERSONAL JOURNAL *\n");
    printf("\t***************************************");

    // Menu.
    while(1){
        printf("\n\n\tMAIN MENU:");
        printf("\n\n\tADD RECORD\t[1]");
        printf("\n\tVIEW RECORD\t[2]");
        printf("\n\tEDIT RECORD\t[3]");
        printf("\n\tDELETE RECORD\t[4]");
        printf("\n\tEDIT PASSWORD\t[5]");
        printf("\n\tEXIT\t\t[6]");
        printf("\n\n\tENTER CHOICE:    ");
        scanf("%d", &menuChoice);

        // Menu options.
        switch(menuChoice){
            case 1:
                addrecord();
                break;

            case 2:
                viewrecord();
                break;

            case 3:
                editrecord();
                break;

            case 4:
                deleterecord();
                break;

            case 5:
                editpassword();
                break;

            case 6:
                printf("\n\n\t.:: UNTIL NEXT TIME ::. ");
                exit(0);
                break;

            default:
                printf("\n\tYOU ENTERED AN INVALID OPTION...");
                printf("\n\tPRESS [ENTER] KEY TO TRY AGAIN.   ");
                getc(stdin);
                break;
            }
        }

    return 0;
}

void addrecord(){
    FILE *file;
    struct record newRecord;
    char another = 'Y', time[10], filename[15];
    bool isAdded;

    // Introduce 'add' menu.
    printf("\n\n\t***************************\n");
    printf("\t* WELCOME TO THE ADD MENU *");
    printf("\n\t***************************");
    
    // Get date for the record.
    printf("\n\n\tENTER A DATE FOR YOUR RECORD [mm-dd-yyyy]:   ");
    fflush(stdin);
    fgets(filename, 15, stdin);
    if(filename[strlen(filename)-1] == '\n'){
        filename[strlen(filename)-1] = '\0';
    }

    // Open file for appending.
    file = fopen(filename, "ab+");
    
    // If file does not exist, open file for writing.
    if(file == NULL){
        file = fopen(filename, "wb+");

        // If opening file for writing fails, display message and return to main menu.
        if(file == NULL){
            fileErrorMessage("write");
            return;
        }
    }

    // While-loop for continuing to enter data sections for the same record.
    while(another == 'Y' || another == 'y'){
        isAdded = false;

        printf("\n\tENTER A TIME [hh:mm]:   ");
        fflush(stdin);
        scanf("%s", time);

        // Send cursor position to the beginning of the file for reading (if appending file).
        rewind(file);

        // Read file. If time section already exists, display message.
        while(fread(&newRecord, sizeof(newRecord), 1, file) == 1){
            if(strcmp(newRecord.time, time) == 0){
                isAdded = true;
                printf("\n\tTHE RECORD ALREADY EXISTS...\n");
            }
        }

        // If time section has not yet been added, add and encryot data to the record struct.
        if(!isAdded){
            strcpy(newRecord.time, time);

            printf("\tENTER NAME:   ");
            fflush(stdin);
            fgets(newRecord.name, 30, stdin);
            if(newRecord.name[strlen(newRecord.name)-1] == '\n'){
                newRecord.name[strlen(newRecord.name)-1] = '\0';
            }
            
            printf("\tENTER PLACE:   ");
            fflush(stdin);
            fgets(newRecord.place, 30, stdin);
            if(newRecord.place[strlen(newRecord.place)-1] == '\n'){
                newRecord.place[strlen(newRecord.place)-1] = '\0';
            }
            
            printf("\tENTER DURATION:   ");
            fflush(stdin);
            fgets(newRecord.duration, 30, stdin);
            if(newRecord.duration[strlen(newRecord.duration)-1] == '\n'){
                newRecord.duration[strlen(newRecord.duration)-1] = '\0';
            }
            
            printf("\tNOTE:   ");
            fflush(stdin);
            fgets(newRecord.note, 1500, stdin);
            if(newRecord.note[strlen(newRecord.note)-1] == '\n'){
                newRecord.note[strlen(newRecord.note)-1] = '\0';
            }

            // Encrypt data.
            encrypt(newRecord.name);
            encrypt(newRecord.place);
            encrypt(newRecord.duration);
            encrypt(newRecord.note);
            
            // Write data from the record struct to the file.
            fwrite(&newRecord, sizeof(newRecord), 1, file);
            printf("\n\tNEW SECTION FOR RECORD, %s HAS BEEN ADDED...\n", filename);
        }

        // Ask to add another time section to the same record.
        printf("\n\tADD ANOTHER SECTION TO THIS RECORD? (Y/N):   ");
        fflush(stdin);
        another = getchar();
    }

    // Close file for appending/writing.
    fclose(file);
}

void viewrecord(){
    FILE *file;
    struct record thisRecord;
    char checkPassword, viewAnother = 'Y', time[10], filename[15];
    int menuOption = 0;
    bool found;

    // Introduce 'viewing' menu.
    printf("\n\n\t*******************************\n");
    printf("\t* WELCOME TO THE VIEWING MENU *");
    printf("\n\t*******************************\n");

    // Check user password. password() returns 0 if correct password; returns 1 if incorrect password.
    checkPassword = password();

    // If password is incorrect, return.
    if(checkPassword != 0){
        return;
    }

    // While loop for continuing to view more records.
    while(viewAnother == 'Y' || viewAnother == 'y'){
        // Present viewing options.
        printf("\n\n\tVIEWING OPTIONS:\n");
        printf("\t----------------\n");
        printf("\n\tVIEW WHOLE RECORD\t\t[1]");
        printf("\n\tVIEW TIME SECTION OF RECORD\t[2]");
        printf("\n\tGO BACK TO MAIN MENU\t\t[3]");
        
        do{
            printf("\n\n\tCHOOSE VIEW OPTION:   ");
            fflush(stdin);
            scanf("%d", &menuOption);
        }while(menuOption < 1 || menuOption > 3);
        
        if(menuOption != 3){
            // Get date/filename of record to be viewed.
            printf("\n\n\tENTER THE DATE OF RECORD TO BE VIEWED [mm-dd-yyyy]:   ");
            fflush(stdin);
            fgets(filename, 15, stdin);
            if(filename[strlen(filename)-1] == '\n'){
                filename[strlen(filename)-1] = '\0';
            }

            // If user attempts to view password file, display error message and return.
            if(strcmp(filename, "PW") == 0 || strcmp(filename, "pw") == 0){
                fileErrorMessage("pwv");
                return;
            }
            
            // Open file for reading.
            file = fopen(filename, "rb");

            // If record does not exist, display message and return to main menu.
            if(file == NULL){
                fileErrorMessage("read");
                return;
            }
        }
        
        switch(menuOption){
            // If menuOption = 1, display entire record.
            case 1:
                printf("\n\n\tENTIRE RECORD FOR %s:", filename);
                printf("\n\t-----------------------------\n");
                
                // Set local record struct with contents of each section.
                while(fread(&thisRecord, sizeof(thisRecord), 1, file) == 1){
                    // Decrypt data.
                    decrypt(thisRecord.name);
                    decrypt(thisRecord.place);
                    decrypt(thisRecord.duration);
                    decrypt(thisRecord.note);
                    
                    // Print data.
                    printf("\n\tTIME: %s", thisRecord.time);
                    printf("\n\tMEETING WITH: %s", thisRecord.name);
                    printf("\n\tMEETING AT: %s", thisRecord.place);
                    printf("\n\tDURATION: %s", thisRecord.duration);
                    printf("\n\tNOTE: %s", thisRecord.note);
                    printf("\n");
                }
                break;

            // If menuOption = 2, get and display user-specified time section of the record.
            case 2:
                printf("\n\tENTER TIME [hh:mm]:   ");
                fgets(time, 10, stdin);
                if(time[strlen(time)-1] == '\n'){
                    time[strlen(time)-1] = '\0';
                }

                rewind(file);
                
                // Set local record struct with contents of each section.
                while(fread(&thisRecord, sizeof(thisRecord), 1, file) == 1){
                    if(strcmp(thisRecord.time, time) == 0){
                        found = true;
                        
                        // Decrypt data.
                        decrypt(thisRecord.name);
                        decrypt(thisRecord.place);
                        decrypt(thisRecord.duration);
                        decrypt(thisRecord.note);
                        
                        break;
                    }
                
                    else{
                        found = false;
                    }
                }
                
                // If specified time section found, display record for that time section.
                if(found){
                    printf("\n\n\tRECORD FOR %s AT %s:", filename, time);
                    printf("\n\t-------------------------------\n");
                    printf("\n\tTIME: %s", thisRecord.time);
                    printf("\n\tMEETING WITH: %s", thisRecord.name);
                    printf("\n\tMEETING AT: %s", thisRecord.place);
                    printf("\n\tDUARATION: %s", thisRecord.duration);
                    printf("\n\tNOTE: %s", thisRecord.note);
                    printf("\n");
                }

                // Else if specified time section not found, display message.
                else if(!found){
                    printf("\n\n\tTIME, %s, DOES NOT EXIST FOR FILE, %s...\n", time, filename);
                }

                break;

            // If menuOption = 3, return.
            case 3:
                return;
                break;
                
            default:
                printf("\n\tINVALID OPTION...");
                break;
        }
        
        // Close file for reading.
        fclose(file);
        
        // Ask user if going back to 'viewing' menu.
        printf("\n\n\tVIEW ANOTHER RECORD? (Y/N):   ");
        fflush(stdin);
        scanf("%c", &viewAnother);
    }
    
    // Encrypt data.
    encrypt(thisRecord.name);
    encrypt(thisRecord.place);
    encrypt(thisRecord.duration);
    encrypt(thisRecord.note);
}

void editrecord(){
    FILE *file;
    struct record thisRecord;
    char editAnother = 'Y', time[10], filename[15];
    int checkPassword, menuOption, editCount = 0;
    bool found;
    
    // Introduce 'editing' menu.
    printf("\n\n\t*******************************\n");
    printf("\t* WELCOME TO THE EDITING MENU *");
    printf("\n\t*******************************\n");

    // Check user password. password() returns 0 if correct password; returns 1 if incorrect password.
    checkPassword = password();

    // If password is incorrect, return.
    if(checkPassword != 0){
        return;
    }

    // Do..while loop for continuing to edit more records.
    while(editAnother == 'Y' || editAnother == 'y'){
        // Editing options.
        printf("\n\n\tEDITING OPTIONS:");
        printf("\n\t-----------------\n");
        printf("\n\tTIME\t\t\t[1]");
        printf("\n\tMEETING PERSON\t\t[2]");
        printf("\n\tMEETING PLACE\t\t[3]");
        printf("\n\tDURATION\t\t[4]");
        printf("\n\tNOTE\t\t\t[5]");
        printf("\n\tWHOLE SECTION\t\t[6]");
        printf("\n\tGO BACK TO MAIN MENU\t[7]");

        // Do..while loop for checking valid menu options.
        do{
            printf("\n\n\tCHOOSE YOUR EDITING OPTION:   ");
            fflush(stdin);
            scanf("%d", &menuOption);
        }while(menuOption < 1 || menuOption > 8);
        
        if(menuOption == 7){
            return;
        }
            
        // Get date/filename of record to be edited.
        printf("\n\n\tENTER THE DATE OF RECORD TO BE EDITED [mm-dd-yyyy]:   ");
        fflush(stdin);
        fgets(filename, 15, stdin);
        if (filename[strlen(filename)-1] == '\n'){
            filename[strlen(filename)-1] = '\0';
        }
        
        // If user attempts to edit password file, display error message and return.
        if(strcmp(filename, "PW") == 0 || strcmp(filename, "pw") == 0){
            fileErrorMessage("pwe");
            return;
        }
        
        // Open file for reading/updating.
        file = fopen(filename, "rb+");

        // If record does not exist, display message and return to main menu.
        if(file == NULL){
            fileErrorMessage("read");
            return;
        }
        
        // Prompt user for time section to edit.
        printf("\n\tENTER THE RECORD TIME SECTION TO EDIT [hh:mm]:   ");
        fflush(stdin);
        fgets(time, 10, stdin);
        if(time[strlen(time)-1] == '\n'){
            time[strlen(time)-1] = '\0';
        }
        
        // Read file, looking for user-specified time section.
        while(fread(&thisRecord, sizeof(thisRecord), 1, file) == 1){
            if(strcmp(thisRecord.time, time) == 0){
                found = true;
                
                // Decrypt data.
                decrypt(thisRecord.name);
                decrypt(thisRecord.place);
                decrypt(thisRecord.duration);
                decrypt(thisRecord.note);
                
                break;
            }
            
            else{
                found = false;
            }
        }
        
        
        // If time section is found, display current record and present editing options.
        if(found){
            // Display current record.
            printf("\n\t-----------------------------------------\n");
            printf("\tCURRENT RECORD FOR, %s, AT %s:", filename, time);
            printf("\n\t-----------------------------------------\n");
            printf("\n\tTIME: %s", thisRecord.time);
            printf("\n\tMEETING WITH: %s", thisRecord.name);
            printf("\n\tMEETING AT: %s", thisRecord.place);
            printf("\n\tDURATION: %s", thisRecord.duration);
            printf("\n\tNOTE: %s\n", thisRecord.note);

            fflush(stdin);
            switch(menuOption){
                case 1:
                    printf("\n\tENTER NEW TIME [hh:mm]:   ");
                    fgets(thisRecord.time, 10, stdin);
                    if(thisRecord.time[strlen(thisRecord.time)-1] == '\n'){
                        thisRecord.time[strlen(thisRecord.time)-1] = '\0';
                    }
                    break;

                case 2:
                    printf("\n\tENTER NEW MEETING PERSON:   ");
                    fgets(thisRecord.name, 30, stdin);
                    if(thisRecord.name[strlen(thisRecord.name)-1] == '\n'){
                        thisRecord.name[strlen(thisRecord.name)-1] = '\0';
                    }
                    break;

                case 3:
                    printf("\n\tENTER NEW MEETING PLACE:   ");
                    fgets(thisRecord.place, 30, stdin);
                    if(thisRecord.place[strlen(thisRecord.place)-1] == '\n'){
                        thisRecord.place[strlen(thisRecord.place)-1] = '\0';
                    }
                    break;

                case 4:
                    printf("\n\tENTER NEW DURATION:   ");
                    fgets(thisRecord.duration, 30, stdin);
                    if(thisRecord.duration[strlen(thisRecord.duration)-1] == '\n'){
                        thisRecord.duration[strlen(thisRecord.duration)-1] = '\0';
                    }
                    break;

                case 5:
                    printf("\n\tENTER NEW NOTE:   ");
                    fgets(thisRecord.note, 1500, stdin);
                    if(thisRecord.note[strlen(thisRecord.note)-1] == '\n'){
                        thisRecord.note[strlen(thisRecord.note)-1] = '\0';
                    }
                    break;

                case 6:
                    printf("\n\tENTER NEW TIME [hh:mm]:   ");
                    fflush(stdin);
                    fgets(thisRecord.time, 10, stdin);
                    if(thisRecord.time[strlen(thisRecord.time)-1] == '\n'){
                        thisRecord.time[strlen(thisRecord.time)-1] = '\0';
                    }

                    printf("\n\tENTER NEW MEETING PERSON:   ");
                    fflush(stdin);
                    fgets(thisRecord.name, 30, stdin);
                    if(thisRecord.name[strlen(thisRecord.name)-1] == '\n'){
                        thisRecord.name[strlen(thisRecord.name)-1] = '\0';
                    }

                    printf("\n\tENTER NEW MEETING PLACE:   ");
                    fflush(stdin);
                    fgets(thisRecord.place, 30, stdin);
                    if(thisRecord.place[strlen(thisRecord.place)-1] == '\n'){
                        thisRecord.place[strlen(thisRecord.place)-1] = '\0';
                    }

                    printf("\n\tENTER NEW DURATION:   ");
                    fflush(stdin);
                    fgets(thisRecord.duration, 30, stdin);
                    if(thisRecord.duration[strlen(thisRecord.duration)-1] == '\n'){
                        thisRecord.duration[strlen(thisRecord.duration)-1] = '\0';
                    }

                    printf("\n\tENTER NEW NOTE:   ");
                    fflush(stdin);
                    fgets(thisRecord.note, 1500, stdin);
                    if(thisRecord.note[strlen(thisRecord.note)-1] == '\n'){
                        thisRecord.note[strlen(thisRecord.note)-1] = '\0';
                    }
                    break;

                // If menuOption = 7, return.
                case 7:
                    return;
                    break;

                default:
                    printf("\n\tINVALID OPTION...\n");
                    break;
            }

            // If editing was successful, display new record and increment editCount.
            editCount++;
            printf("\n\tEDITING COMPLETED...\n");
            printf("\n\t------------------------------------\n");
            printf("\tNEW RECORD FOR, %s, AT %s:\n", filename, thisRecord.time);
            printf("\t------------------------------------\n");
            printf("\n\tTIME: %s", thisRecord.time);
            printf("\n\tMEETING WITH: %s", thisRecord.name);
            printf("\n\tMEETING AT: %s", thisRecord.place);
            printf("\n\tDURATION: %s", thisRecord.duration);
            printf("\n\tNOTE: %s", thisRecord.note);
            
            // Encrypt data.
            encrypt(thisRecord.name);
            encrypt(thisRecord.place);
            encrypt(thisRecord.duration);
            encrypt(thisRecord.note);
            
            // Go back one section from where cursor ended in file, and write edited data.
            fseek(file, -sizeof(thisRecord), SEEK_CUR);
            fwrite(&thisRecord, sizeof(thisRecord), 1, file);
            
            // Go back one section from where cursor ended in file, and read edited data.
            fseek(file, -sizeof(thisRecord), SEEK_CUR);
            fread(&thisRecord, sizeof(thisRecord), 1, file);
            
            // Close file for reading/updating.
            fclose(file);

            // Ask user if going back to 'editing' menu.
            printf("\n\n\tWOULD YOU LIKE TO EDIT ANOTHER RECORD? (Y/N):   ");
            fflush(stdin);
            scanf(" %c", &editAnother);
        }
        
        // If user-specified time section is not found, display message.
        else if(!found){
            printf("\n\tTHE TIME, %s, FOR RECORD, %s, DOES NOT EXIST...\n", time, filename);
            printf("\n\tWOULD YOU LIKE TO TRY AGAIN? (Y/N):   ");
            fflush(stdin);
            scanf(" %c", &editAnother);
        }
    }

    // Close file for reading/updating.
    fclose(file);

    // Display number of files successfully edited.
    if(editCount == 1){
        printf("\n\t%d FILE/SECTION HAS BEEN EDITED...\n", editCount);
    }
    
    else if(editCount > 1){
        printf("\n\t%d FILES/SECTIONS HAVE BEEN EDITED...\n", editCount);
    }
    
    else{
        printf("\n\tNO FILES/SECTIONS EDITED...\n");
    }
}

int password(){
    FILE *file;
    char passwordEntered[15], decryptedPassword[15], currChar;
    int i = 0;

    // Allow user three attempts to enter correct password.
    printf("\n\t.:: FOR SECURITY REASONS, ONLY 3 ATTEMPTS ARE ALLOWED ::.\n");

    for(int j = 0; j < 3; j++){
        i = 0;

        // Prompt user to enter password.
        printf("\n\tENTER CURRENT PASSWORD:  ");
        fflush(stdin);
        fgets(passwordEntered, 15, stdin);
        if(passwordEntered[strlen(passwordEntered)-1] == '\n'){
            passwordEntered[strlen(passwordEntered)-1] = '\0';
        }

        // Open password file for reading.
        file = fopen("PW", "r");

        // If password file does not exist, display message and return to main menu.
        if(file == NULL){
            fileErrorMessage("system");
            return 1;
        }

        // Get characters from password file, decrypt each character, and store decrypted password.
        while(1){
            currChar = fgetc(file);

            if(currChar == EOF){
                decryptedPassword[i] = '\0';
                break;
            }

            decryptedPassword[i] = currChar - 5;
            i++;
        }

        // If user-entered password matches decrypted password, access granted; return 0.
        if(strcmp(passwordEntered, decryptedPassword) == 0){
            printf("\n\n\tACCESS GRANTED...\n");
            return 0;
        }

        // Else, display message.
        else printf("\n\tINVALID PASSWORD...\n");
    }

    // If three failed attempts have been made, display message and return 1.
    printf("\n\t.:: YOU HAVE REACHED THE MAXIMUM ATTEMPTS ALLOWED. ACCESS DENIED ::.");
    printf("\n\tPRESS [ENTER] KEY TO GO BACK TO MAIN MENU.   ");
    getc(stdin);
    
    return 1;
}

void editpassword(){
    FILE *file;
    char newPassword[15], confirmNewPassword[15], currChar;
    int checkPassword, i;
    bool passwordConfirmed;
    
    // Introduce 'password editing' section.
    printf("\n\n\t*****************\n");
    printf("\t* EDIT PASSWORD *");
    printf("\n\t*****************\n");
 
    // Open password file for reading.
    file = fopen("PW", "rb");

    // If password file does not exist, password is default. Write a new password file.
    if(file == NULL){
        fileErrorMessage("pwu");
        file = fopen("PW", "wb");
        
        // If opening for writing fails, display message and return to main menu.
        if(file == NULL){
            fileErrorMessage("system");
            return;
        }
    }
    
    // Close password file for reading/writing.
    fclose(file);

    // Check user password. password() returns 0 if correct password; returns 1 if incorrect password.
    checkPassword = password();

    // If password is incorrect, return.
    if(checkPassword == 1){
        return;
    }

    // Do..while loop until new password confirmation is successful.
    do{
        // If password entered is correct, prompt user to enter and confirm new password.
        if(checkPassword == 0){
            printf("\n\n\tENTER NEW PASSWORD:  ");
            fflush(stdin);
            fgets(newPassword, 15, stdin);
            if(newPassword[strlen(newPassword)-1] == '\n'){
                newPassword[strlen(newPassword)-1] = '\0';
            }

            printf("\n\tCONFIRM NEW PASSWORD:  ");
            fgets(confirmNewPassword, 15, stdin);
            if(confirmNewPassword[strlen(confirmNewPassword)-1] == '\n'){
                confirmNewPassword[strlen(confirmNewPassword)-1] = '\0';
            }

            // If new password has been successfully confirmed, write new password to password file.
            if(strcmp(newPassword, confirmNewPassword) == 0){
                passwordConfirmed = true;
                
                // Open password file again for writing.
                file = fopen("PW", "wb");

                // If opening for writing fails, display message and return to main menu.
                if(file == NULL){
                    fileErrorMessage("write");
                    return;
                }

                // Reset i.
                i = 0;
                
                // Encrypt each character of the password, and write it to the password file.
                while(newPassword[i] != '\0'){
                    currChar = newPassword[i];
                    putc(currChar + 5, file);
                    i++;
                }

                // Null-terminate and close the password file for writing.
                putc(EOF, file);
                fclose(file);
            }

            // If password editing is unsuccessful, display message.
            else{
                passwordConfirmed = false;
                printf("\n\tTHE NEW PASSWORD DOES NOT MATCH.");
            }
        }
    }while(!passwordConfirmed);

    // If password edit is successful, display message.
    printf("\n\n\tPASSWORD CHANGED...");
    printf("\n\tPRESS [ENTER] KEY TO GO BACK TO MAIN MENU.   ");
    getc(stdin);
}

void deleterecord(){
    FILE *thisFile, *tempFile;
    struct record thisRecord;
    char filename[15], deleteAnother = 'Y' , time[10];
    int menuOption, checkPassword;
    bool found;

    // Introduce 'deletion' menu.
    printf("\n\n\t**************************\n");
    printf("\t* WELCOME TO DELETE MENU *");
    printf("\n\t**************************\n");
    
    // Check user password. password() returns 0 if correct password; returns 1 if incorrect password.
    checkPassword = password();

    // If password is incorrect, return.
    if(checkPassword == 1){
        return;
    }

    // While loop while user wishes to delete records.
    while(deleteAnother == 'Y' || deleteAnother == 'y'){
        printf("\n\n\tDELETION OPTIONS:");
        printf("\n\t-----------------\n");
        printf("\n\tDELETE WHOLE RECORD\t\t[1]");
        printf("\n\tDELETE TIME SECTION OF RECORD\t[2]");
        printf("\n\tGO BACK TO MAIN MENU\t\t[3]");

        // Do..while loop for checking valid menu options.
        do{
            // Prompt user for deletion option.
            printf("\n\n\tCHOOSE DELETION OPTION:   ");
            scanf("%d", &menuOption);
        }while(menuOption < 1 || menuOption > 3);
        
        switch(menuOption){
            // If menuOption = 1, delete the whole file.
            case 1:
                // Get date/filename of whole file to be deleted.
                printf("\n\tENTER THE DATE OF RECORD TO BE DELETED [mm-dd-yyyy]:   ");
                fflush(stdin);
                fgets(filename, 15, stdin);
                if(filename[strlen(filename)-1] == '\n'){
                    filename[strlen(filename)-1] = '\0';
                }

                // If user attempts to delete password file, display error message and return.
                if(strcmp(filename, "PW") == 0 || strcmp(filename, "pw") == 0){
                    printf("\n\tFATAL ERROR! CANNOT DELETE PASSWORD FILE!");
                    printf("\n\tPRESS [ENTER] KEY TO GO BACK TO MAIN MENU.   ");
                    getc(stdin);
                    return;
                }
                
                // Open specified file for reading.
                thisFile = fopen(filename, "rb");

                // If file does not exist, display message and return to main menu.
                if(thisFile == NULL){
                    fileErrorMessage("read");
                    return;
                }

                // Close specified file for reading.
                fclose(thisFile);

                // Delete whole file and display message.
                remove(filename);
                printf("\n\tDELETED SUCCESFULLY...\n");
                break;

            // If menuOption = 2, delete the user-specified time section of the specified file.
            case 2:
                // Get date/filename of file for user-specified time section deletion.
                printf("\n\tENTER THE DATE OF RECORD [mm-dd-yyyy]:   ");
                fflush(stdin);
                fgets(filename, 15, stdin);
                if(filename[strlen(filename)-1] == '\n'){
                    filename[strlen(filename)-1] = '\0';
                }

                // If user attempts to delete password file, display error message and return.
                if(strcmp(filename, "PW") == 0 || strcmp(filename, "pw") == 0){
                    printf("\n\tFATAL ERROR! CANNOT DELETE PASSWORD FILE!");
                    printf("\n\tPRESS [ENTER] KEY TO GO BACK TO MAIN MENU.   ");
                    getc(stdin);
                    return;
                }
                
                // Open specified file again for reading.
                thisFile = fopen(filename, "rb");

                // If file does not exist, display message and return to main menu.
                if(thisFile == NULL){
                    fileErrorMessage("read");
                    return;
                }

                // Open temp file for writing.
                tempFile = fopen("temp", "wb");

                // If opening file for writing fails, display message and return to main menu.
                if(tempFile == NULL){
                    fileErrorMessage("write");
                    return;
                }

                // Get time for section of specified file to be deleted.
                printf("\n\tENTER THE TIME SECTION TO BE DELETED [hh:mm]:   ");
                fflush(stdin);
                fgets(time, 10, stdin);
                if(time[strlen(time)-1] == '\n'){
                    time[strlen(time)-1] = '\0';
                }

                // Store file data into thisRecord struct, and look for user-specified time section.
                while(fread(&thisRecord, sizeof(thisRecord), 1, thisFile) == 1){
                    if(strcmp(thisRecord.time, time) == 0){
                        found = true;
                        break;
                    }
                    
                    else{
                        found = false;
                    }
                }

                // Send cursor position to the beginning of the file for reading.
                rewind(thisFile);
                
                // If user-specified time section is not found, display message.
                if(!found){
                    printf("\n\tTHE TIME, %s, FOR RECORD, %s, DOES NOT EXIST...\n", time, filename);
                }
                
                // If user-specified time section is found, write all other sections to temp file.
                else if(found){
                    while(fread(&thisRecord, sizeof(thisRecord), 1, thisFile) == 1){
                        if(strcmp(thisRecord.time, time) != 0){
                            fwrite(&thisRecord, sizeof(thisRecord), 1, tempFile);
                        }
                    }
                    
                    // Close specified file for reading.
                    fclose(thisFile);
                    
                    // Close temp file for writing.
                    fclose(tempFile);

                    // Remove original specified file and replace it with temp file.
                    remove(filename);
                    rename("temp", filename);

                    // Display message when deletion is complete.
                    printf("\n\tDELETED SUCCESFULLY...\n");
                }
                break;

            // If menuOption = 3, return.
            case 3:
                return;
                break;
                
            default:
                printf("\n\tYOU ENTERED AN INVALID OPTION...");
                break;
        }

        // Ask user if going back to 'deletion' menu.
        printf("\n\tDELETE ANOTHER RECORD? (Y/N):   ");
        fflush(stdin);
        scanf("%c", &deleteAnother);
    }
}

void encrypt(char *data){
    int i = 0;
    
    while(data[i] != '\0'){
        if(data[i] == '\0') break;
        else{
            data[i] += 5;
            i++;
        }
    }
}

void decrypt(char *data){
    int i = 0;
    
    while(data[i] != '\0'){
        if(data[i] == '\0') break;
        else{
            data[i] -= 5;
            i++;
        }
    }
}

void fileErrorMessage(char* type){
    if(strcmp(type, "write") == 0){
        printf("\n\tSYSTEM ERROR...");
    }
    
    else if(strcmp(type, "read") == 0){
        printf("\n\tTHE RECORD DOES NOT EXIST...");
    }
    
    else if(strcmp(type, "system") == 0){
        printf("\n\tERROR: PASSWORD UNSET OR SYSTEM FAILURE...");
    }
    
    else if(strcmp(type, "pwu") == 0){
        printf("\n\tNO PASSWORD SET: YOUR CURRENT PASSWORD IS [ENTER] KEY...\n");
        return;
    }
    
    else if(strcmp(type, "pwv") == 0){
        printf("\n\tFATAL ERROR! CANNOT VIEW PASSWORD FILE!");
    }
    
    else if(strcmp(type, "pwe") == 0){
        printf("\n\tFATAL ERROR! CANNOT EDIT PASSWORD FILE!");
    }

    printf("\n\tPRESS [ENTER] KEY TO GO BACK TO MAIN MENU.   ");
    getc(stdin);
}
