import java.io.*;
import java.util.*;

public class Entry{
	private String time;
	private String place;
    private String mood;
	private String entry;

	// Entry constructor...
	public Entry(){

	}

	public int addEntry(){
		
		// Char, menuChoice, is used for user-input menu choice.
		// Char, addAnother, is used for user option to continue adding/adding to entries.
		char menuChoice = '0', addAnother = 'Y';
		
        // Boolean, validChoice, is used for validating menuChoice.
        boolean validChoice = false;
        
        // String, filename, is used for user-input filename.
		String filename = "";
		
		// Local object declarations for class function use.
		Entry newEntry = new Entry();
		Errors errors = new Errors();
		
        // Entry, thisEntry, holds data from some entry file for parsing.
        Entry thisEntry = new Entry();
        
		// Scanner object for user input.
		Scanner in = new Scanner(System.in);
			
		// File, file Scanner, and FileWriter objects for entry files.
		File file = null;
		Scanner fileScan = null;
		FileWriter fileWriter = null;
        
        // Introduce 'add' menu.
        System.out.println("\n\n\t************");
        System.out.println("\t* ADD MENU *");
        System.out.println("\t************");
        System.out.println("\n\tAdd new entry\t\t[1]");
        System.out.println("\tAdd to existing entry\t[2]");
        System.out.println("\tBack to main menu\t[3]");
        System.out.println("\tClose journal\t\t[4]");
        
		// Do-while loop until valid menu choice is entered.
		do{
			System.out.print("\n\tSelect ADD option:\t");

			try{
				menuChoice = in.nextLine().charAt(0);
				if(menuChoice < 49 || menuChoice > 52) ;
				else validChoice = true;
			}
			catch(StringIndexOutOfBoundsException e){
				/**/
			}
		}while(!validChoice);
			
		// If adding new data...
		if(menuChoice != '3' && menuChoice != '4'){
			
			// ...prompt user for the filename/date of the new entry
			System.out.print("\n\tENTER ENTRY FILENAME AS DATE [mm-dd-yyyy]:   ");
			filename = in.nextLine();
			if(filename.equals("")) filename = " ";
			
			// ...and set File object.
			file = new File(filename);
		}
    
		// Rule-switch for menu options.
		switch(menuChoice){
				
			// If menuChoice is 1...
			case ('1') -> {
				
				// ...if entry already exists, return to main menu.
				if(file.exists()){
					System.out.println("\n\t(!) ENTRY [" + filename + "] ALREADY EXISTS...");
					return 0;
				}
				
				// ...else, create the file.
				else{ 				
					try{
						file.createNewFile();
					}
					catch(IOException e){
						errors.errorMessage("write", "");
						//e.printStackTrace();
					}
				}
				
				break;
			}

			// If menuChoice is 2 and entry does not exist, return to main menu.
			case ('2') -> {
				if(!file.exists()){
					System.out.println("\n\t(!) ENTRY [" + filename + "] DOES NOT EXIST...");
					return 0;
				}
				
				break;
			}
				
			// If menuChoice is 3, return to main menu.
			case ('3') -> {return 0;}
		
			// If menuChoice is 4, exit program.
			case ('4') -> {return 1;}
			
			// Default returns to main menu.
			default -> {return 0;}
		}
		
		// While-loop for continuing to enter sections in the same entry.
		while(addAnother == 'Y' || addAnother == 'y'){
	
			// Get time from user to be used as section header.
			System.out.print("\n\tWHAT TIME IS IT? [hh:mm]am/pm:   ");
			newEntry.time = in.nextLine();
            if(newEntry.time.equals("")) newEntry.time = " ";
            
            // Set file Scanner object.
            try{
                fileScan = new Scanner(file);
            }
			catch(IOException e){
                errors.errorMessage("write", "");
                //e.printStackTrace();
            }
            
            // While there are entries, continue searching for user-specified time.
            while(fileScan.hasNext()){
                
                // Set thisEntry object with encrypted data from each section of the entry file.
                thisEntry.time = fileScan.nextLine();
                thisEntry.place = fileScan.nextLine();
                thisEntry.mood = fileScan.nextLine();
                thisEntry.entry = fileScan.nextLine();

                // Decrypt thisEntry time data.
                thisEntry.time = encryptDecrypt(thisEntry.time, false, true);
                
                // If matching time was found, display message and prompt user for a different time value.
                if(thisEntry.time.equals(newEntry.time)){
                    System.out.println("\n\t(!) SECTION [" + newEntry.time + "] ALREADY EXISTS...");
					
					// Get time from user to be used as section header.
					System.out.print("\n\tWHAT TIME IS IT? [hh:mm]am/pm:   ");
					newEntry.time = in.nextLine();
					if(newEntry.time.equals("")) newEntry.time = " ";
					
					// Reset file Scanner object to beginning of entry file.
					try{
						fileScan = new Scanner(file);
					}
					catch(IOException e){
						errors.errorMessage("write", "");
						//e.printStackTrace();
					}
                }
            }

			// Close file Scanner object.
			if(fileScan != null) fileScan.close();
            
			// Get newEntry.place.
			System.out.print("\tWHERE ARE YOU?   ");
			newEntry.place = in.nextLine();
            if(newEntry.place.equals("")) newEntry.place = " ";
            
			// Get newEntry.mood.
			System.out.print("\tHOW ARE YOU FEELING?   ");
			newEntry.mood = in.nextLine();
            if(newEntry.mood.equals("")) newEntry.mood = " ";
            
			// Get newEntry.entry.
			System.out.print("\tENTRY:   ");
			newEntry.entry = in.nextLine();
            if(newEntry.entry.equals("")) newEntry.entry = " ";
            
			// For display purposes.
			String tempTime = newEntry.time;
			
			// Encrypt data.
			newEntry.time = encryptDecrypt(newEntry.time, true, false);
			newEntry.place = encryptDecrypt(newEntry.place, true, false);
			newEntry.mood = encryptDecrypt(newEntry.mood, true, false);
            newEntry.entry = encryptDecrypt(newEntry.entry, true, false);

			// Add newlines to each section.
			newEntry.time += "\n";
			newEntry.place += "\n";
            newEntry.mood += "\n";
			newEntry.entry += "\n";
            
			// // Set FileWriter object, and write newEntry data to the file.
			try{
				fileWriter = new FileWriter(filename, true);
				fileWriter.append(newEntry.time);
				fileWriter.append(newEntry.place);
				fileWriter.append(newEntry.mood);
				fileWriter.append(newEntry.entry);
				
				// Close FileWriter object.
				fileWriter.close();
			}
			catch(IOException e){
				errors.errorMessage("write", "");
				//e.printStackTrace();
			}

			// Display confirmation of added entry.
			System.out.println("\n\tSECTION [" + tempTime + "] FOR ENTRY [" + filename + "] HAS BEEN ADDED...");

			// Ask user if adding another time section to the same entry.
			System.out.print("\n\tADD ANOTHER SECTION TO THIS ENTRY? (Y/N):   ");
			try{
				addAnother = in.nextLine().charAt(0);
			}
			catch(StringIndexOutOfBoundsException e){
				addAnother = 'N';
			}
		}
        
        return 0;
	}
	
	public int viewEntry(){
		
		// Char, menuChoice, is used for user-input menu choice.
		// Char, viewAnother, is used for user option to continue viewing entries.
		char menuChoice = '0', viewAnother = 'Y';
	
        // Boolean, validChoice, is used for validating menuChoice.
		// Boolean, found, is used for determining whether a user-specified entry was found.
		boolean validChoice = false, found = false;
		
		// Int variable, checkPassword, is used for the return value of password().
		int checkPassword = 0;
        
		// String, filename, is used to user-input filename.
		// String, time, is used for finding a user-specified time section in the entry file.
		String filename = "", time = "";
		
		// Local object declarations for class function use.
		Password password = new Password();
		Errors errors = new Errors();
		
        // Entry, thisEntry, holds data from some entry file for parsing.
        Entry thisEntry = new Entry();
        
        // Scanner object for user input.
        Scanner in = new Scanner(System.in);
        
        // File and file Scanner objects for entry files.
		File file = null;
        Scanner fileScan = null;

		// Check user password. password() returns 0 if correct password and returns 1 if incorrect password.
		checkPassword = password.password();

		// If password is incorrect, return to main menu.
		if(checkPassword == 1) return 0;

		// While-loop for continuing to view more entries.
		while(viewAnother == 'Y' || viewAnother == 'y'){
			
            // Reset validChoice boolean.
            validChoice = false;
            
			// Present 'view' menu.
			System.out.println("\n\t*************");
			System.out.println("\t* VIEW MENU *");
			System.out.println("\t*************");
			System.out.println("\n\tView whole entry\t\t[1]");
			System.out.println("\tView time section of entry\t[2]");
			System.out.println("\tBack to main menu\t\t[3]");
            System.out.println("\tClose journal\t\t\t[4]");
            
			// Do-while loop until valid menu choice is entered.
			do{
				System.out.print("\n\tSelect VIEW option:\t");

				try{
					menuChoice = in.nextLine().charAt(0);
					if(menuChoice < 49 || menuChoice > 52) ;
					else validChoice = true;
				}
				catch(StringIndexOutOfBoundsException e){
					/**/
				}
			}while(!validChoice);

			// If viewing an entry, prompt user for the date of the entry to be viewed.
			if(menuChoice == '1' || menuChoice == '2'){
				
				// Get filename/date of entry to be viewed.
				System.out.print("\n\tENTER THE FILENAME OF ENTRY TO BE VIEWED [mm-dd-yyyy]:   ");
				filename = in.nextLine();
                if(filename.equals("")) filename = " ";
                
				// If user attempts to view password file, display error message, and return to main menu.
				if(filename.equals("PW") || filename.equals("pw")){
					errors.errorMessage("pwv", "");
					return 0;
				}

				// Set File object.
				file = new File(filename);

				// If entry does not exist, display message, and return to main menu.
				if(!file.exists()){
					errors.errorMessage("read", filename);
					break;
				}

				// Set file Scanner object.
				try{
					fileScan = new Scanner(file);
				}
				catch(IOException e){
					errors.errorMessage("write", "");
					//e.printStackTrace();
					break;
				}
			}

			// Rule-switch for menu options.
			switch(menuChoice){
	
				// If menuChoice is 1, display entire entry.
				case ('1') -> {
					
					// Display the entire entry.
					System.out.println("\n\t------------------------------");
					System.out.println("\tENTIRE ENTRY FOR [" + filename + "]: ");
					System.out.println("\t------------------------------");
					
					// While there are entries, continue displaying them to the user.
					while(fileScan.hasNext()){
						
						// Set thisEntry object with encrypted data from each section of the entry file.
						thisEntry.time = fileScan.nextLine();
						thisEntry.place = fileScan.nextLine();
						thisEntry.mood = fileScan.nextLine();
						thisEntry.entry = fileScan.nextLine();

						// Decrypt and print thisEntry object data.
						System.out.println("\n\tTIME:\t" + encryptDecrypt(thisEntry.time, false, true));
						System.out.println("\tPLACE:\t" + encryptDecrypt(thisEntry.place, false, true));
						System.out.println("\tMOOD:\t" + encryptDecrypt(thisEntry.mood, false, true));
                        thisEntry.entry = encryptDecrypt(thisEntry.entry, false, true);
                        System.out.print("\tENTRY:\t");
                        
                        /* Format entry section for display. */
                        
                        // Variables to track the entry string index, number of characters printed, entry string length, and individual characters of the entry section.
                        int entryStringIndex = 0, charactersPrinted = 0, entryLength = thisEntry.entry.length();
                        Character entryCharacter = thisEntry.entry.charAt(0);
                        
                        // While there is still more of the entry section to print...
                        while(entryStringIndex != entryLength){
                            
                            // ...get and print each character one by one
                            entryCharacter = thisEntry.entry.charAt(entryStringIndex);
                            System.out.print(entryCharacter);

                            // ...and increment charactersPrinted.
                            charactersPrinted++;
                            
                            // If 75 or more characters have been printed, and a space or end of sentence has been reached...
                            if(charactersPrinted >= 75 && (entryCharacter == ' ' || entryCharacter == '.' || entryCharacter == ',')){
								
								//  ...print a newline with two tabs
                                System.out.print("\n\t\t");
								
								// ...and reset charactersPrinted.
                                charactersPrinted = 0;
                            }
                            
                            // ...increment entryStringIndex.
                            entryStringIndex++;
                        }
                        
                        System.out.println();
					}
					
					break;
				}
				
				// If menuChoice is 2, get and display user-specified time section of the entry.
				case ('2') -> {
					
					// Prompt user for the time section of the entry to be viewed.
					System.out.print("\n\tENTER TIME [hh:mm]:   ");
					time = in.nextLine();
                    if(time.equals("")) time = " ";
                    
					// While there are entries, continue searching for the user-specified time section.
					while(fileScan.hasNext()){
						
						// Set thisEntry object with encrypted data from each section of the entry file.
                        thisEntry.time = fileScan.nextLine();
                        thisEntry.place = fileScan.nextLine();
                        thisEntry.mood = fileScan.nextLine();
                        thisEntry.entry = fileScan.nextLine();
						
						// Decrypt thisEntry time data.
						thisEntry.time = encryptDecrypt(thisEntry.time, false, true);
							
						// If the time for this section matches user-input, break from while-loop.
						if(time.equals(thisEntry.time)){
							found = true;
							break;
						}

						// Else, continue search until no more entries.
						else found = false;
					}

					// If specified time section was found, display entry for that time section.
					if(found){
						System.out.println("\n\t------------------------------------");
						System.out.println("\tENTRY FOR [" + filename + "] AT [" + time + "]:");
						System.out.println("\t------------------------------------\n");
						System.out.println("\tTIME:\t" + thisEntry.time);
						System.out.println("\tPLACE:\t" + encryptDecrypt(thisEntry.place, false, true));
						System.out.println("\tMOOD:\t" + encryptDecrypt(thisEntry.mood, false, true));
						thisEntry.entry = encryptDecrypt(thisEntry.entry, false, true);
                        System.out.print("\tENTRY:\t");
                        
                        /* Format entry section for display. */
                        
                        // Variables to track the entry string index, number of characters printed, entry string length, and individual characters of the entry section.
                        int entryStringIndex = 0, charactersPrinted = 0, entryLength = thisEntry.entry.length();
                        Character entryCharacter = thisEntry.entry.charAt(0);
                        
                        // While there is still more of the entry section to print...
                        while(entryStringIndex != entryLength){
                            
                            // ...get and print each character one by one
                            entryCharacter = thisEntry.entry.charAt(entryStringIndex);
                            System.out.print(entryCharacter);

                            // ...and increment charactersPrinted.
                            charactersPrinted++;
                            
                            // If 75 or more characters have been printed, and a space or end of sentence has been reached...
                            if(charactersPrinted >= 75 && (entryCharacter == ' ' || entryCharacter == '.' || entryCharacter == ',')){
								
								//  ...print a newline with two tabs
                                System.out.print("\n\t\t");
								
								// ...and reset charactersPrinted.
                                charactersPrinted = 0;
                            }
                            
                            // ...increment entryStringIndex.
                            entryStringIndex++;
                        }
                        
                        System.out.println();
					}

					// Else, if specified time section was not found, display message.
					else if(!found) System.out.println("\n\t(!) TIME [" + time + "] FOR ENTRY [" + filename + "] DOES NOT EXIST...");
					break;
				}
				
				// If menuChoice is 3, return to main menu.
				case ('3') -> {return 0;}
				
				// If menuChoice is 4, exit program.
				case ('4') -> {return 1;}
				
				// Default returns to main menu.
				default -> {return 0;}
			}

			// Ask user if viewing another entry.
			System.out.print("\n\tVIEW ANOTHER ENTRY? (Y/N):   ");
			try{
				viewAnother = in.nextLine().charAt(0);
			}
			catch(StringIndexOutOfBoundsException e){
				viewAnother = 'N';
			}
		}
        
		// Close file Scanner object and return to main menu.
		if(fileScan != null) fileScan.close();
        return 0;
	}
	
	public int editEntry(){

		// Char, menuChoice, is used for user-input menu choice.
        // Char, editAnother, is used for user option to continue editing entries.
        char menuChoice = '0', editAnother = 'Y';
        
		// Boolean, validChoice, is used for validating menuChoice.
		// Boolean, found, is used for determining whether a user-specified entry was found.
		// Booleans, wholeSection and sectionPart, are used for determining the data to be overwritten.
        boolean validChoice = false, found = false, wholeSection = false, sectionPart = false;
        
        // Int variable, checkPassword, is used for the return value of password().
        // Int variable, editCount, is used for counting the number of edits made.
        int checkPassword = 0, editCount = 0;
        
        // String, time, is used to find user-specified time sections of a entry.
        // String, filename, is used to user-input filename.
        String time = "", filename = "";
        
        // Local object declarations for class function use.
        Password password = new Password();
        Errors errors = new Errors();
        
        // Entry objects, oldEntry and newEntry, are used for replacing entry data.
        Entry oldEntry = new Entry();
		Entry newEntry = new Entry();
        
        // Scanner object for user input.
        Scanner in = new Scanner(System.in);
        
        // File, file Scanner, and FileWriter objects for entry files.
        File file = null;
        Scanner fileScan = null;
		FileWriter fileWriter = null;
		
        // Check user password. password() returns 0 if correct password and returns 1 if incorrect password.
        checkPassword = password.password();

        // If password is incorrect, return to main menu.
        if(checkPassword == 1) return 0;

        // While-loop for continuing to edit more entries.
        while(editAnother == 'Y' || editAnother == 'y'){
            
			// Get filename/date of entry to be edited.
			System.out.print("\n\tENTER THE FILENAME OF ENTRY TO BE EDITED [mm-dd-yyyy]:   ");
			filename = in.nextLine();
			if(filename.equals("")) filename = " ";

			// If user attempts to edit password file, display error message, and return to main menu.
			if(filename.equals("PW") || filename.equals("pw")){
				errors.errorMessage("pwe", "");
				return 0;
			}

			// Set File object.
			file = new File(filename);

			// If entry does not exist, display message and return to main menu.
			if(!file.exists()){
				errors.errorMessage("read", filename);
				return 0;
			}

			// Display current entry.
			System.out.println("\n\t-------------------------------");
			System.out.println("\tCURRENT ENTRY FOR [" + filename + "]:");
			System.out.println("\t-------------------------------");

			// Set file Scanner object.
			try{
				fileScan = new Scanner(file);
			}
			catch(IOException e){
				errors.errorMessage("write", "");
				//e.printStackTrace();
			}
			
			// While there are entries, continue displaying them to the user.
			while(fileScan.hasNext()){

				// Set oldEntry object with encrypted data from each section of the entry file.
				oldEntry.time = fileScan.nextLine();
				oldEntry.place = fileScan.nextLine();
				oldEntry.mood = fileScan.nextLine();
				oldEntry.entry = fileScan.nextLine();

				// Decrypt and print oldEntry object data.
				System.out.println("\n\tTIME:\t" + encryptDecrypt(oldEntry.time, false, true));
				System.out.println("\tPLACE:\t" + encryptDecrypt(oldEntry.place, false, true));
				System.out.println("\tMOOD:\t" + encryptDecrypt(oldEntry.mood, false, true));
				oldEntry.entry = encryptDecrypt(oldEntry.entry, false, true);
				System.out.print("\tENTRY:\t");

				/* Format entry section for display. */

				// Variables to track the entry string index, number of characters printed, entry string length, and individual characters of the entry section.
				int entryStringIndex = 0, charactersPrinted = 0, entryLength = oldEntry.entry.length();
				Character entryCharacter = oldEntry.entry.charAt(0);

				// While there is still more of the entry section to print...
				while(entryStringIndex != entryLength){

					// ...get and print each character one by one
					entryCharacter = oldEntry.entry.charAt(entryStringIndex);
					System.out.print(entryCharacter);

					// ...and increment charactersPrinted.
					charactersPrinted++;

					// If 75 or more characters have been printed, and a space or end of sentence has been reached...
					if(charactersPrinted >= 75 && (entryCharacter == ' ' || entryCharacter == '.' || entryCharacter == ',')){

						//  ...print a newline with two tabs
						System.out.print("\n\t\t");

						// ...and reset charactersPrinted.
						charactersPrinted = 0;
					}

					// ...increment entryStringIndex.
					entryStringIndex++;
				}

				System.out.println();
			}

			// Close file Scanner object.
			if(fileScan != null) fileScan.close();

			// Prompt user for the time section of the entry to be edited.
			System.out.print("\n\tENTER TIME SECTION TO EDIT [hh:mm]am/pm:   ");
			time = in.nextLine();
			if(time.equals("")) time = " ";

			// Set file Scanner object.
			try{
				fileScan = new Scanner(file);
			}
			catch(IOException e){
				errors.errorMessage("write", "");
				//e.printStackTrace();
			}

			// While there are entries, continue searching for the user-specified time section.
			while(fileScan.hasNext()){

				// Set oldEntry object with encrypted data from each section of the entry file.
				oldEntry.time = fileScan.nextLine();
				oldEntry.place = fileScan.nextLine();
				oldEntry.mood = fileScan.nextLine();
				oldEntry.entry = fileScan.nextLine();

				// Decrypt oldEntry time data.
				oldEntry.time = encryptDecrypt(oldEntry.time, false, true);

				// If the time for this section matches user-input, break from while-loop.
				if(time.equals(oldEntry.time)){
					found = true;
					break;
				}

				// Else, continue search until no more entries.
				else found = false;
			}

			// Close file Scanner object.
			if(fileScan != null) fileScan.close();
			
			// If user-specified time section is not found, display message and return to main menu.
			if(!found){
				System.out.println("\n\t(!) TIME [" + time + "] FOR ENTRY [" + filename + "] DOES NOT EXIST...");
				return 0;
			}
			
            // Reset validChoice and printSelect booleans.
            validChoice = false;
			
            // Present 'edit' menu.
            System.out.println("\n\t*************");
            System.out.println("\t* EDIT MENU *");
            System.out.println("\t*************");
			System.out.println("\n\tEdit entire entry for time section [" + time + "]\t[1]");
			System.out.println("\tEdit one line of time section [" + time + "]\t\t[2]");
            System.out.println("\tBack to main menu\t\t\t\t[3]");
            System.out.println("\tClose journal\t\t\t\t\t[4]");
            
   			// Do-while loop until valid menu choice is entered.
			do{
				System.out.print("\n\tSelect EDIT option:\t");

				try{
					menuChoice = in.nextLine().charAt(0);
					if(menuChoice < 49 || menuChoice > 52) ;
					else validChoice = true;
				}
				catch(StringIndexOutOfBoundsException e){
					/**/
				}
			}while(!validChoice);

			// Rule-switch for menu options.
			switch(menuChoice){
				
				// If menuChoice is 1, edit the entire time section for this entry.
				case ('1') -> {
					
					// Set wholeSection to true and sectionPart to false.
					wholeSection = true;
					sectionPart = false;
					
					// Prompt user for new time value.
					System.out.print("\n\tENTER NEW TIME [hh:mm]am/pm:   ");
					newEntry.time = in.nextLine();
					if(newEntry.time.equals("")) newEntry.time = " ";
							
					// Set file Scanner object.
					try{
						fileScan = new Scanner(file);
					}
					catch(IOException e){
						errors.errorMessage("write", "");
						//e.printStackTrace();
					}
            
					// While there are entries, continue searching for user-specified time.
					while(fileScan.hasNext()){

						// Set oldEntry object with encrypted data from each section of the entry file.
						oldEntry.time = fileScan.nextLine();
						oldEntry.place = fileScan.nextLine();
						oldEntry.mood = fileScan.nextLine();
						oldEntry.entry = fileScan.nextLine();

						// Decrypt oldEntry time data.
						oldEntry.time = encryptDecrypt(oldEntry.time, false, true);

						// If matching time was found, display message and prompt user for a different time value.
						if(oldEntry.time.equals(newEntry.time)){
							System.out.println("\n\t(!) TIME SECTION [" + newEntry.time + "] ALREADY EXISTS...");
							
							System.out.print("\n\tENTER NEW TIME [hh:mm]am/pm:   ");
							newEntry.time = in.nextLine();
							if(newEntry.time.equals("")) newEntry.time = " ";			

							// Reset file Scanner object to beginning of entry file.
							try{
								fileScan = new Scanner(file);
							}
							catch(IOException e){
								errors.errorMessage("write", "");
								//e.printStackTrace();
							}	
						}
					}
					
					// Close file Scanner object.
					if(fileScan != null) fileScan.close();
					            
					// Get newEntry.place.
					System.out.print("\tENTER NEW PLACE:   ");
					newEntry.place = in.nextLine();
					if(newEntry.place.equals("")) newEntry.place = " ";
							
					// Get newEntry.mood.
					System.out.print("\tENTER NEW MOOD:   ");
					newEntry.mood = in.nextLine();
					if(newEntry.mood.equals("")) newEntry.mood = " ";
							
					// Get newEntry.entry.
					System.out.print("\tENTER NEW ENTRY:   ");
					newEntry.entry = in.nextLine();
					if(newEntry.entry.equals("")) newEntry.entry = " ";

					// Encrypt data.
					newEntry.time = encryptDecrypt(newEntry.time, true, false);
					newEntry.place = encryptDecrypt(newEntry.place, true, false);
					newEntry.mood = encryptDecrypt(newEntry.mood, true, false);
					newEntry.entry = encryptDecrypt(newEntry.entry, true, false);

					// Add newlines to each section.
					newEntry.time += "\n";
					newEntry.place += "\n";
					newEntry.mood += "\n";
					newEntry.entry += "\n";

					// Increment editCount.
					editCount += 1;
					break;
				}
				
				// If menuChoice is 2, edit one line of the time section for this entry.
				case ('2') -> {

					// Set sectionPart to true and wholeSection to false.
					sectionPart = true;
					wholeSection = false;
					
					// Reset validChoice and printSelect booleans.
					validChoice = false;

					// Display editing options for individual lines of the entry section.
					System.out.println("\n\tEdit time\t\t[1]");
					System.out.println("\tEdit place\t\t[2]");
					System.out.println("\tEdit mood\t\t[3]");
					System.out.println("\tEdit entry\t\t[4]");
					System.out.println("\tBack to main menu\t[5]");
					System.out.println("\tClose journal\t\t[6]");

					// Do-while loop until valid menu choice is entered.
					do{
						System.out.print("\n\tSelect EDIT option:\t");

						try{
							menuChoice = in.nextLine().charAt(0);
							if(menuChoice < 49 || menuChoice > 54) ;
							else validChoice = true;
						}
						catch(StringIndexOutOfBoundsException e){
							/**/
						}
					}while(!validChoice);

					System.out.println();
					
					// Edit the user-specified section.
					switch(menuChoice){
						
						// If menuChoice is 1, get newEntry.time.
						case ('1') -> {
							System.out.print("\tENTER NEW TIME [hh:mm]am/pm:   ");
							newEntry.time = in.nextLine();
							if(newEntry.time.equals("")) newEntry.time = " ";
							
							// Set file Scanner object.
							try{
								fileScan = new Scanner(file);
							}
							catch(IOException e){
								errors.errorMessage("write", "");
								//e.printStackTrace();
							}

							// While there are entries, continue searching for user-specified time.
							while(fileScan.hasNext()){

								// Set oldEntry object with encrypted data from each section of the entry file.
								oldEntry.time = fileScan.nextLine();
								oldEntry.place = fileScan.nextLine();
								oldEntry.mood = fileScan.nextLine();
								oldEntry.entry = fileScan.nextLine();

								// Decrypt oldEntry time data.
								oldEntry.time = encryptDecrypt(oldEntry.time, false, true);

								// If matching time was found, display message and prompt user for a different time value.
								if(oldEntry.time.equals(newEntry.time)){
									System.out.println("\n\t(!) TIME SECTION [" + newEntry.time + "] ALREADY EXISTS...");

									System.out.print("\n\tENTER NEW TIME [hh:mm]am/pm:   ");
									newEntry.time = in.nextLine();
									if(newEntry.time.equals("")) newEntry.time = " ";			

									// Reset file Scanner object to beginning of entry file.
									try{
										fileScan = new Scanner(file);
									}
									catch(IOException e){
										errors.errorMessage("write", "");
										//e.printStackTrace();
									}	
								}
							}

							// Close file Scanner object.
							if(fileScan != null) fileScan.close();
							break;
						}

						// If menuChoice is 2, get newEntry.place.
						case ('2') -> {
							System.out.print("\tENTER NEW PLACE:   ");
							newEntry.place = in.nextLine();
							if(newEntry.place.equals("")) newEntry.place = " ";
							break;
						}

						// If menuChoice is 3, get newEntry.mood.
						case ('3') -> {
							System.out.print("\tENTER NEW MOOD:   ");
							newEntry.mood = in.nextLine();
							if(newEntry.mood.equals("")) newEntry.mood = " ";
							break;
						}

						// If menuChoice is 4, get newEntry.entry.
						case ('4') -> {
							System.out.print("\tENTER NEW ENTRY:   ");
							newEntry.entry = in.nextLine();
							if(newEntry.entry.equals("")) newEntry.entry = " ";
							break;
						}

						// If menuChoice is 5, return to main menu.
						case ('5') -> {return 0;}

						// If menuChoice is 6, exit program.
						case ('6') -> {return 1;}

						// Default returns to main menu.
						default -> {return 0;}
					}

					// Encrypt certain data depending on the editing choice.
					if(wholeSection || (sectionPart && menuChoice == '1')) newEntry.time = encryptDecrypt(newEntry.time, true, false);
					else if(wholeSection || (sectionPart && menuChoice == '2')) newEntry.place = encryptDecrypt(newEntry.place, true, false);
					else if(wholeSection || (sectionPart && menuChoice == '3')) newEntry.mood = encryptDecrypt(newEntry.mood, true, false);
					else if(wholeSection || (sectionPart && menuChoice == '4')) newEntry.entry = encryptDecrypt(newEntry.entry, true, false);

					// Add newlines to each section.
					newEntry.time += "\n";
					newEntry.place += "\n";
					newEntry.mood += "\n";
					newEntry.entry += "\n";
					
					// Increment editCount.
					editCount += 1;
					break;
				}

				// If menuChoice is 3, return to main menu.
				case ('3') -> {return 0;}
				
				// If menuChoice is 4, exit program.
				case ('4') -> {return 1;}
				
				// Default returns to main menu.
				default -> {return 0;}
			}

			// Rename entry file to 'temp'.
			File temp = new File("temp");
			file.renameTo(temp);
			
			// Reset File object.
			file = new File("temp");
			
			// Set file Scanner object.
			try{
				fileScan = new Scanner(file);
			}
			catch(IOException e){
				errors.errorMessage("write", "");
				//e.printStackTrace();
			}
							
			// Set FileWriter object.			
			try{
				fileWriter = new FileWriter(filename, true);
			}
			catch(IOException e){
				errors.errorMessage("write", "");
				//e.printStackTrace();
			}
			
			// While there are entries, continue adding data to entry file depending on the editing choice.
			while(fileScan.hasNext()){

				// Get contents of each section into oldEntry object.
				oldEntry.time = fileScan.nextLine();
				oldEntry.place = fileScan.nextLine();
				oldEntry.mood = fileScan.nextLine();
				oldEntry.entry = fileScan.nextLine();

				// Decrypt oldEntry time data.
				String testTime = encryptDecrypt(oldEntry.time, false, true);
				
				// Add newlines to oldEntry data.
				oldEntry.time += "\n";
				oldEntry.place += "\n";
				oldEntry.mood += "\n";
				oldEntry.entry += "\n";
					
				// If the time for this section matches the user-specified time section to edit...
				if(time.equals(testTime)){
					
					// ...if editing the whole section, write the new section to the new entry file
					if(wholeSection){
						try{
							fileWriter.append(newEntry.time);
							fileWriter.append(newEntry.place);
							fileWriter.append(newEntry.mood);
							fileWriter.append(newEntry.entry);
						}
						catch(IOException e){
							errors.errorMessage("write", "");
							//e.printStackTrace();
						}
					}
					
					// ...else, if editing only a part of the section
					else if(sectionPart){

						// ...write each section to the new entry file accordingly.
						try{
							
							// Rule-switch for menu options.
							switch (menuChoice) {
								
								// If 'time' has a new value, write newEntry.time, and oldEntry for the other section parts.
								case '1' -> {
									fileWriter.append(newEntry.time);
									fileWriter.append(oldEntry.place);
									fileWriter.append(oldEntry.mood);
									fileWriter.append(oldEntry.entry);
									break;
								}
								
								// If 'place' has a new value, write newEntry.place, and oldEntry for the other section parts.
								case '2' -> {
									fileWriter.append(oldEntry.time);
									fileWriter.append(newEntry.place);
									fileWriter.append(oldEntry.mood);
									fileWriter.append(oldEntry.entry);
									break;
								}
								
								// If 'mood' has a new value, write newEntry.mood, and oldEntry for the other section parts.
								case '3' -> {
									fileWriter.append(oldEntry.time);
									fileWriter.append(oldEntry.place);
									fileWriter.append(newEntry.mood);
									fileWriter.append(oldEntry.entry);
									break;
								}
								
								// If 'entry' has a new value, write newEntry.entry, and oldEntry for the other section parts.
								case '4' -> {
									fileWriter.append(oldEntry.time);
									fileWriter.append(oldEntry.place);
									fileWriter.append(oldEntry.mood);
									fileWriter.append(newEntry.entry);
									break;
								}
								
								default -> {}
							}
						}
						catch(IOException e){
							errors.errorMessage("write", "");
							//e.printStackTrace();
						}
					}
				}

				// Else, if the time for this section does not match the user-specified time section to edit...
				else{

					// ...write all oldEntry section parts.
					try{
						fileWriter.append(oldEntry.time);
						fileWriter.append(oldEntry.place);
						fileWriter.append(oldEntry.mood);
						fileWriter.append(oldEntry.entry);
					}
					catch(IOException e){
						errors.errorMessage("write", "");
						//e.printStackTrace();
					}
				}
			}
			
			// Close file Scanner and FileWriter objects.
			if(fileScan != null) fileScan.close();
			try{
				fileWriter.close();	
			}
			catch(IOException e){
				errors.errorMessage("write", "");
				//e.printStackTrace();
			}
			
			// Delete the old file.
			file.delete();

			// Ask user if editing another entry.
			System.out.print("\n\tEDIT ANOTHER ENTRY? (Y/N):   ");
			try{
				editAnother = in.nextLine().charAt(0);
			}
			catch(StringIndexOutOfBoundsException e){
				editAnother = 'N';
			}
		}

        // Display the number of successful edits made. Output depends on number of edits.
        if(editCount == 1) System.out.println("\n\t(1) EDIT MADE SUCCESSFULLY...");

        else if(editCount > 1) System.out.println("\n\t(" + editCount + ") EDITS MADE SUCCESSFULLY...");

		else System.out.println("\n\tNO EDITS MADE...");

        return 0;
	}
	
	public int deleteEntry(){
		
		// Char, menuChoice, is used for user-input menu choice.
		// Char, deleteAnother, is used for user option to continue deleting entries.
		// Char, confirmDeletion, is used for confirming deletion of data to user.
        char menuChoice = '0', deleteAnother = 'Y', confirmDeletion = 'N';
		
		// Boolean, validChoice, is used for validating menuChoice.
		// Boolean, found, is used for determining whether a user-specified entry was found.
        boolean validChoice = false, found = false;
        
		// Int variable, checkPassword, is used for the return value of password().
        // Int variable, deleteCount, is used for counting the number of deletions.
        int checkPassword = 0, deleteCount = 0;
       
        // String, time, is used to find user-specified time sections of a entry.
        // String, filename, is used to user-input filename.
		String time = "", filename = "";

		// Local object declarations for class function use.
        Password password = new Password();
        Errors errors = new Errors();
		
		// Entry, thisEntry, holds data from some entry file for parsing.
        Entry thisEntry = new Entry();
		
		// Scanner object for user input.
        Scanner in = new Scanner(System.in);
		
		// File, file Scanner, and FileWriter objects for entry files.
        File file = null;
        Scanner fileScan = null;
		FileWriter fileWriter = null;

        // Check user password. password() returns 0 if correct password and returns 1 if incorrect password.
        checkPassword = password.password();

        // If password is incorrect, return to main menu.
        if(checkPassword == 1) return 0;

        // While-loop for continuing to delete more entries.
        while(deleteAnother == 'Y' || deleteAnother == 'y'){
			
			// Get the filename from the user, and display the entire entry.
			System.out.print("\n\tENTER ENTRY FILENAME TO VIEW 'DELETE' MENU [mm-dd-yyyy]:   ");
			filename = in.nextLine();
			if(filename.equals("")) filename = " ";

			// If user attempts to delete password file, display error message, and return to main menu.
			if(filename.equals("PW") || filename.equals("pw")){
				errors.errorMessage("pwe", "");
				return 0;
			}

			// Set File object.
			file = new File(filename);

			// If entry does not exist, display message and return to main menu.
			if(!file.exists()){
				errors.errorMessage("read", filename);
				return 0;
			}

			// Set file Scanner object.
			try{
				fileScan = new Scanner(file);
			}
			catch(IOException e){
				errors.errorMessage("write", "");
				//e.printStackTrace();
			}

			// Display the entry.
			System.out.println("\n\t-----------------------");
			System.out.println("\tENTRY FOR [" + filename + "]: ");
			System.out.println("\t-----------------------");

			// While there are entries, continue displaying them to the user.
			while(fileScan.hasNext()){

				// Set thisEntry object with encrypted data from each section of the entry file.
				thisEntry.time = fileScan.nextLine();
				thisEntry.place = fileScan.nextLine();
				thisEntry.mood = fileScan.nextLine();
				thisEntry.entry = fileScan.nextLine();

				// Decrypt and print thisEntry object data.
				System.out.println("\n\tTIME:\t" + encryptDecrypt(thisEntry.time, false, true));
				System.out.println("\tPLACE:\t" + encryptDecrypt(thisEntry.place, false, true));
				System.out.println("\tMOOD:\t" + encryptDecrypt(thisEntry.mood, false, true));
				thisEntry.entry = encryptDecrypt(thisEntry.entry, false, true);
				System.out.print("\tENTRY:\t");

				/* Format entry section for display. */

				// Variables to track the entry string index, number of characters printed, entry string length, and individual characters of the entry section.
				int entryStringIndex = 0, charactersPrinted = 0, entryLength = thisEntry.entry.length();
				Character entryCharacter = thisEntry.entry.charAt(0);

				// While there is still more of the entry section to print...
				while(entryStringIndex != entryLength){

					// ...get and print each character one by one
					entryCharacter = thisEntry.entry.charAt(entryStringIndex);
					System.out.print(entryCharacter);

					// ...and increment charactersPrinted.
					charactersPrinted++;

					// If 75 or more characters have been printed, and a space or end of sentence has been reached...
					if(charactersPrinted >= 75 && (entryCharacter == ' ' || entryCharacter == '.' || entryCharacter == ',')){

						//  ...print a newline with two tabs
						System.out.print("\n\t\t");

						// ...and reset charactersPrinted.
						charactersPrinted = 0;
					}

					// ...increment entryStringIndex.
					entryStringIndex++;
				}

				System.out.println();
			}

			// Close file Scanner object.
			if(fileScan != null) fileScan.close();
			
			// Reset validChoice and printSelect booleans.
            validChoice = false;
			
			// Present 'delete' menu.
			System.out.println("\n\t***************");
			System.out.println("\t* DELETE MENU *");
			System.out.println("\t***************");
            System.out.println("\n\tDelete whole entry\t\t[1]");
            System.out.println("\tDelete time section of entry\t[2]");
            System.out.println("\tBack to main menu\t\t[3]");
			System.out.println("\tClose journal\t\t\t[4]");

			// Do-while loop until valid menu choice is entered.
			do{
				System.out.print("\n\tSelect EDIT option:\t");

				try{
					menuChoice = in.nextLine().charAt(0);
					if(menuChoice < 49 || menuChoice > 52) ;
					else validChoice = true;
				}
				catch(StringIndexOutOfBoundsException e){
					/**/
				}
			}while(!validChoice);
			
			// Rule-switch for menu options.
            switch(menuChoice){
				
                // If menuChoice is 1, delete the entire file.
                case ('1') -> {
					
					// Confirm deletion of the entry.
					System.out.println("\n\t(!) NOTE: DELETIONS CANNOT BE UNDONE");
					System.out.print("\n\tAre you sure you would like to delete the entire entry file [" + filename + "]? (Y/N):   ");
					try{
						confirmDeletion = in.next().charAt(0);		
					}
					catch(StringIndexOutOfBoundsException e){
						confirmDeletion = 'N';
					}
					
                    // If deletion is confirmed...
					if(confirmDeletion == 'y' || confirmDeletion == 'Y'){
						
						// ...delete the entire entry file
						file.delete();
						
						// ...display confirmation message
						System.out.println("\n\tDELETED SUCCESFULLY...");

						// ...and increment deleteCount.
						deleteCount += 1;
					}
					
                    break;
				}

                // If menuChoice is 2, delete only the user-specified time section of the entry file.
                case ('2') -> {
			
                    // Get time for section of specified file to be deleted.
                    System.out.print("\n\tENTER THE TIME SECTION TO BE DELETED [hh:mm]:   ");
					time = in.nextLine();
					if(time.equals("")) time = " ";
							
					// Set file Scanner object.
					try{
						fileScan = new Scanner(file);
					}
					catch(IOException e){
						errors.errorMessage("write", "");
						//e.printStackTrace();
					}
				
					// While there are entries, continue searching for the user-specified time section.
					while(fileScan.hasNext()){

						// Set thisEntry object with encrypted data from each section of the entry file.
						thisEntry.time = fileScan.nextLine();
						thisEntry.place = fileScan.nextLine();
						thisEntry.mood = fileScan.nextLine();
						thisEntry.entry = fileScan.nextLine();

						// Decrypt thisEntry data.
						thisEntry.time = encryptDecrypt(thisEntry.time, false, true);

						// If the time for this section matches user-input, break from while-loop.
						if(time.equals(thisEntry.time)){
							found = true;
							break;
						}

						// Else, continue search until no more entries.
						else found = false;
					}
					
					// Close file Scanner object.
					if(fileScan != null) fileScan.close();
					
					// If user-specified time section is not found, display message and return to main menu.
					if(!found){
						System.out.println("\n\t(!) TIME [" + time + "] FOR ENTRY [" + filename + "] DOES NOT EXIST...");
						return 0;
					}
					
					// Confirm deletion of the entry.
					System.out.println("\n\t(!) NOTE: DELETIONS CANNOT BE UNDONE");
					System.out.print("\n\tAre you sure you would like to delete the time entry [" + time + "] from [" + filename + "]? (Y/N):   ");
					try{
						confirmDeletion = in.next().charAt(0);		
					}
					catch(StringIndexOutOfBoundsException e){
						confirmDeletion = 'N';
					}
					
                    // Once deletion is confirmed write all other sections to a new entry file.
					if(confirmDeletion == 'y' || confirmDeletion == 'Y'){
					
						// Rename entry file to 'temp'.
						File temp = new File("temp");
						file.renameTo(temp);

						// Reset File object.
						file = new File("temp");

						// Set file Scanner object.
						try{
							fileScan = new Scanner(file);
						}
						catch(IOException e){
							errors.errorMessage("write", "");
							//e.printStackTrace();
						}

						// Set FileWriter object.			
						try{
							fileWriter = new FileWriter(filename, true);
						}
						catch(IOException e){
							errors.errorMessage("write", "");
							//e.printStackTrace();
						}

						// While there are entries, continue writing to new entry file.
						while(fileScan.hasNext()){

							// Set thisEntry object with encrypted data from each section of the entry file.
							thisEntry.time = fileScan.nextLine();
							thisEntry.place = fileScan.nextLine();
							thisEntry.mood = fileScan.nextLine();
							thisEntry.entry = fileScan.nextLine();

							// Decrypt thisEntry time data.
							String testTime = encryptDecrypt(thisEntry.time, false, true);

							// Add newlines to thisEntry data.
							thisEntry.time += "\n";
							thisEntry.place += "\n";
							thisEntry.mood += "\n";
							thisEntry.entry += "\n";
				
							// If user-specified time does not equal thisEntry time data...
							if(!time.equals(testTime)){

								// ...write the time section to the new entry file.
								try{
									fileWriter.append(thisEntry.time);
									fileWriter.append(thisEntry.place);
									fileWriter.append(thisEntry.mood);
									fileWriter.append(thisEntry.entry);
								}
								catch(IOException e){
									errors.errorMessage("write", "");
									//e.printStackTrace();
								}
							}
						}

						// Close file Scanner and FileWriter objects.
						if(fileScan != null) fileScan.close();
						try{
							fileWriter.close();	
						}
						catch(IOException e){
							errors.errorMessage("write", "");
							//e.printStackTrace();
						}

						// Delete original entry file.
						file.delete();

						// Display message when deletion is complete.
						System.out.println("\n\tDELETED SUCCESFULLY...");

						// Increment deleteCount.
						deleteCount += 1;
					}
					
                    break;
				}

				// If menuChoice is 3, return to main menu.
				case ('3') -> {return 0;}
				
				// If menuChoice is 4, exit program.
				case ('4') -> {return 1;}
				
				// Default returns to main menu.
				default -> {return 0;}
            }

            // Ask user if deleting another entry/entry section.
            System.out.print("\n\tDELETE ANOTHER ENTRY? (Y/N):   ");
			deleteAnother = in.next().charAt(0);
			try{
				deleteAnother = in.nextLine().charAt(0);
			}
			catch(StringIndexOutOfBoundsException e){
				deleteAnother = 'N';
			}
        }
		
		// Display the number of successful deletions. Output depends on number of deletions.
        if(deleteCount == 1) System.out.println("\n\t(1) DELETION PERFORMED SUCCESSFULLY...");

        else if(deleteCount > 1) System.out.println("\n\t(" + deleteCount + ") DELETIONS PERFORMED SUCCESSFULLY...");

		else System.out.println("\n\tNO DELETIONS PERFORMED...");
		
        return 0;
	}
	
	protected String encryptDecrypt(String data, boolean encrypt, boolean decrypt){
		
		// Int variable, i, is used for string length counter.
        // Int variable, ascii, is used for holding ASCII value of a given character.
        // Int variable, length, is used for determining the length of the given string.
		int i = 0, ascii = 0, length = data.length();

		// String, new_string, is used for holding the newly encrypted/decrypted string.
    	String newString = "";
		
		// Character object, character, is used for holding each character of the string.
		Character character = data.charAt(0);
		
		// While there is more string length, encrypt/decrypt.
		while(i != length){
			
			// Get each character and its ASCII value one by one.
			character = data.charAt(i);
			ascii = character;
		
			// Check if encrypting or decrypting.
			if(encrypt) ascii += 5;
			else if(decrypt) ascii -= 5;
			
			// Concatenate the newly encrypted/decrypted charater to newString.
			character = (char)ascii;
			newString += character;
			
			// Increment string length counter.
			i++;
		}
				
		// Return the encrypted/decrypted string.
		return newString;
	}
}
