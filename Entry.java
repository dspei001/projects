import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Scanner;

/**
 * Entry class performs add, view, edit, delete, encrypt/decrypt,
 * and various other operations on journal entry text files;
 * NOTE: The functions in this class are listed in 2 groups,
 *		 "MENU FUNCTIONS" and "UTILITIES", where "MENU FUNCTIONS"
 *		 performs the expected operations based on the program menu,
 *		 and where "UTILITIES" functions assist the "MENU FUNCTIONS".
 * @author Debra-Lee Speight
 */
public class Entry{
	private final Errors errors;
	private final Scanner in;
	private Scanner fileScan;
	private File file;
	private String filename;
	private String time;
	private String place;
    private String mood;
	private String entryBody;

	/**
	 * Constructor instantiates class members.
	 */
	Entry(){
		errors = new Errors();
		in = new Scanner(System.in);
		fileScan = null;
		file = null;
		filename = null;
		time = "time";
		place = "place";
		mood = "mood";
		entryBody = "entry";
	}


	/************************************************************/
	/*                     MENU FUNCTIONS                       */
	/************************************************************/


	/**
	 * Creates and writes a new section to a newly created entry file.
	 * @return 1 upon successful add; 0 otherwise
	 *		   (used for addCount in Menus)
	 */
	int addNewEntry(){
		getFilenameFromUser();
		if(entryExists()){
			errors.errorMessage("fileExists", filename, "");
			return 0;
		}
		else{
			try{file.createNewFile();}
			catch(IOException e){errors.errorMessage("create", "", "");}
			createSection();
			writeSection(time);
			System.out.println("\n\tSECTION [" + time + "] HAS BEEN ADDED TO [" + filename + "]");
			return 1;
		}
	}

	/**
	 * Creates and writes a new section to an existing entry file.
	 * @return 1 upon successful add; 0 otherwise
	 *		   (used for addCount in Menus)
	 */
	int addToExisting(){
		getFilenameFromUser();
		if(entryExists()){
			createSection();
			writeSection(time);
			System.out.println("\n\tSECTION [" + time + "] HAS BEEN ADDED TO [" + filename + "]");
			return 1;
		}
		else if(!entryExists()) errors.errorMessage("file", filename, "");
		return 0;
	}

	/**
	 * Displays the entire user-specified entry file if it exists.
	 * @return true if viewing entire entry is successful; false otherwise
	 */
	boolean viewEntry(){
		getFilenameFromUser();
		if(entryExists()){
			displayEntry();
			return true;
		}
		else errors.errorMessage("file", filename, "");
		return false;
	}

	/**
	 * Displays only user-specified entry section if it exists.
	 * @return true if viewing entry section is successful; false otherwise
	 */
	boolean viewSection(){
		getFilenameFromUser();
		if(entryExists()){
			getTimeFromUser("VIEW");
			if(sectionExists()){
				displaySection();
				return true;
			}
			else errors.errorMessage("section", filename, time);
		}
		else errors.errorMessage("file", filename, "");
		return false;
	}

	/**
	 * Edits a whole section of an entry file if it exists.
	 * @return 1 upon successful edit; 0 otherwise
	 *		   (used for editCount in Menus)
	 */
	int editSection(){
		if(viewEntry()){
			getTimeFromUser("EDIT");
			if(sectionExists()){
				if(editAllSectionFields())
					if(file.delete()) return 1;
			}
			else errors.errorMessage("section", filename, time);
		}
		return 0;
	}

	/**
	 * Edits one section field of an entry file.
	 * @return 1 upon successful edit; 0 otherwise
	 *		   (used for editCount in Menus)
	 */
	int editSectionField(){
		if(viewEntry()){
			getTimeFromUser("EDIT");
			if(sectionExists()){
				editOneSectionField();
				if(file.delete()) return 1;
			}
			else errors.errorMessage("section", filename, time);
		}
		return 0;
	}

	/**
	 * Deletes the entire user-specified entry file if it exists.
	 * @return 1 upon successful deletion; 0 otherwise
	 *		   (used for deleteCount in Menus)
	 */
	int deleteEntry(){
		if(viewEntry()){
			if(confirmDeletion("")){
				if(file.delete()){
					System.out.println("\n\t[" + filename + "] DELETED SUCCESSFULLY");
					return 1;
				}
			}
		}
		return 0;
	}

	/**
	 * Deletes only user-specified entry section if it exists.
	 * @return 1 upon successful deletion; 0 otherwise
	 *		   (used for deleteCount in Menus)
	 */
	int deleteSection(){
		if(viewEntry()){
			getTimeFromUser("DELETE");
			if(sectionExists()){
				if(confirmDeletion(" section [" + time + "] for entry")){
					renameFileToTemp();
					writeAllSectionsExcept(time);
					if(file.delete()){
						System.out.println("\n\tSECTION [" + time + "] DELETED SUCCESSFULLY");
						return 1;
					}
				}
			}
			else errors.errorMessage("section", filename, time);
		}
		return 0;
	}


	/************************************************************/
	/*                        UTILITIES                         */
	/************************************************************/


	/**
	 * Creates a new entry section if it does not already exist.
	 */
	private void createSection(){
		validateTime();
		getPlaceFromUser();
		getMoodFromUser();
		getEntryBodyFromUser();
	}

	/**
	 * Displays an entire entry under a header.
	 */
	private void displayEntry(){
		System.out.println("\n\t------------------------------");
		System.out.println("\tENTIRE ENTRY FOR [" + filename + "]: ");
		System.out.println("\t------------------------------");

		try{fileScan = new Scanner(file);}
		catch(IOException e){errors.errorMessage("scanner", "", "");}
		while(fileScan.hasNext()){
			time = decryptEntry(fileScan.nextLine());
			printSectionFields();
		}
		fileScan.reset();
	}

	/**
	 * Displays an entry section under a header.
	 */
	private void displaySection(){
		System.out.println("\n\t------------------------------------");
		System.out.println("\tENTRY FOR [" + filename + "] AT [" + time + "]:");
		System.out.println("\t------------------------------------");

		try{fileScan = new Scanner(file);}
		catch(IOException e){errors.errorMessage("scanner", "", "");}
		while(fileScan.hasNext()){
			String thisTime = decryptEntry(fileScan.nextLine());
			if(!thisTime.equals(time)) for(int i = 0; i < 3; i++) fileScan.nextLine();
			else printSectionFields();
		}
		fileScan.reset();
	}

	/**
	 * Prints all section fields.
	 */
	private void printSectionFields(){
		System.out.println("\n\tTIME: " + time);
		System.out.println("\tPLACE: " + (place = decryptEntry(fileScan.nextLine())));
		System.out.println("\tMOOD: " + (mood = decryptEntry(fileScan.nextLine())));
		System.out.print("\tENTRY: ");
		entryBody = decryptEntry(fileScan.nextLine());
		formatEntryBody();
	}

	/**
	 * Displays entryBody in formatted fashion for easier viewing.
	 */
	private void formatEntryBody(){
		int index = 0, charsPrinted = 0, length = entryBody.length();
		while(index != length){
			Character thisCharacter = entryBody.charAt(index);
			System.out.print(thisCharacter);
			charsPrinted++;

			if(charsPrinted >= 63 && thisCharacter == ' '){
				System.out.print("\n\t\t");
				charsPrinted = 0;
			}
			index++;
		}
		System.out.println();
	}

	/**
	 * Allows user to change all section fields and rewrites the entry.
	 * @return modified : true if section modified; false otherwise
	 */
	private boolean editAllSectionFields(){
		boolean modified = false;
		System.out.println("\n\t[NOW EDITING ENTRY]");
		String holdTime = time;
		renameFileToTemp();
		try{fileScan = new Scanner(file);}
		catch(IOException e){errors.errorMessage("scanner", "", "");}
		while(fileScan.hasNext()){
			String thisTime = decryptEntry(fileScan.nextLine());
			if(thisTime.equals(holdTime)){
				createSection();
				writeSection(time);
				modified = true;
				System.out.println("\n\t[" + filename + "] MODIFIED SUCCESSFULLY");
				for(int i = 0; i < 3; i++) fileScan.nextLine();
			}
			else{
				place = decryptEntry(fileScan.nextLine());
				mood = decryptEntry(fileScan.nextLine());
				entryBody = decryptEntry(fileScan.nextLine());
				writeSection(thisTime);
			}
		}
		fileScan.reset();
		return modified;
	}

	/**
	 * Gets the specific field for editing from user.
	 * @return a String designating the field to edit
	 */
	private String getFieldToEdit(){
		int editChoice = 0;
		System.out.print("\n\tSelect the section to edit:");
		System.out.print("\n\tEdit TIME\t[1]\n\tEdit PLACE\t[2]");
		System.out.println("\n\tEdit MOOD\t[3]\n\tEdit ENTRY\t[4]");

		while(editChoice < 49 || editChoice > 52){
			System.out.print("\n\tSELECT OPTION: \t");
			try{editChoice = in.nextLine().charAt(0);}
			catch(StringIndexOutOfBoundsException e){}
		}
		if(editChoice == 49) return "TIME";
		else if(editChoice == 50) return "PLACE";
		else if(editChoice == 51) return "MOOD";
		else if(editChoice == 52) return "ENTRY";
		else return null;
	}

	/**
	 * Allows user to change one section field and rewrites the entry.
	 */
	private void editOneSectionField(){
		String field = getFieldToEdit();
		String holdTime = time;
		renameFileToTemp();
		try{fileScan = new Scanner(file);}
		catch(IOException e){errors.errorMessage("scanner", "", "");}
		while(fileScan.hasNext()){
			String thisTime = decryptEntry(fileScan.nextLine());
			if(thisTime.equals(holdTime)){
				editThisField(field, thisTime);
				System.out.println("\n\t[" + filename + "] MODIFIED SUCCESSFULLY");
			}
			else{
				place = decryptEntry(fileScan.nextLine());
				mood = decryptEntry(fileScan.nextLine());
				entryBody = decryptEntry(fileScan.nextLine());
			}

			if(thisTime.equals(holdTime) && field.equals("TIME")) writeSection(time);
			else writeSection(thisTime);
		}
		fileScan.reset();
	}

	/**
	 * Edits one field of an entry section given the specified field.
	 * @param field
	 * @param thisTime : used if specifying the time field
	 */
	private void editThisField(String field, String thisTime){
		System.out.println("\n\t[NOW EDITING ENTRY]");
		if(field.equals("TIME")){
			validateTime();
			place = decryptEntry(fileScan.nextLine());
			mood = decryptEntry(fileScan.nextLine());
			entryBody = decryptEntry(fileScan.nextLine());
		}
		else if(field.equals("PLACE")){
			time = thisTime;
			getPlaceFromUser();
			fileScan.nextLine();
			mood = decryptEntry(fileScan.nextLine());
			entryBody = decryptEntry(fileScan.nextLine());
		}
		else if(field.equals("MOOD")){
			time = thisTime;
			place = decryptEntry(fileScan.nextLine());
			getMoodFromUser();
			fileScan.nextLine();
			entryBody = decryptEntry(fileScan.nextLine());
		}
		else if(field.equals("ENTRY")){
			time = thisTime;
			place = decryptEntry(fileScan.nextLine());
			mood = decryptEntry(fileScan.nextLine());
			getEntryBodyFromUser();
			fileScan.nextLine();
		}
	}

	/**
	 * Writes a given time section to an entry file after encrypting.
	 * @param thisTime : time section to write
	 */
	private void writeSection(String thisTime){
		try{
			FileWriter fileWriter = new FileWriter(filename, true);
			fileWriter.append(encryptEntry(thisTime) + "\n");
			fileWriter.append(encryptEntry(place) + "\n");
			fileWriter.append(encryptEntry(mood) + "\n");
			fileWriter.append(encryptEntry(entryBody) + "\n");
			fileWriter.close();
		}catch(IOException e){errors.errorMessage("filewriter", "", "");}
	}

	/**
	 * Writes all but one section of an entry to a new file.
	 * @param time : the section to skip
	 */
	private void writeAllSectionsExcept(String time){
		try{fileScan = new Scanner(file);}
		catch(IOException e){errors.errorMessage("scanner", "", "");}
		while(fileScan.hasNext()){
			String thisTime = decryptEntry(fileScan.nextLine());
			place = decryptEntry(fileScan.nextLine());
			mood = decryptEntry(fileScan.nextLine());
			entryBody = decryptEntry(fileScan.nextLine());

			if(!thisTime.equals(time)) writeSection(thisTime);
		}
		fileScan.reset();
	}

	/**
	 * Renames file to "temp" for entry modifications and deletions.
	 */
	private void renameFileToTemp(){
		File temp = new File("temp");
		file.renameTo(temp);
		file = new File("temp");
	}

	/**
	 * Asks user to confirm the deletion of a section (if specified) or entire entry.
	 * @param deleteSectionMsg : given message about section to delete, if specified
	 * @return true if deletion confirmed by user; false otherwise
	 */
	private boolean confirmDeletion(String deleteSectionMsg){
		int confirm = 0;
		do{
			System.out.println("\n\t(!) ALERT: DELETIONS CANNOT BE UNDONE");
			System.out.print("\tAre you sure you would like to delete" + deleteSectionMsg);
			System.out.print(" [" + filename + "]? (Y/N):   ");
			try{confirm = in.nextLine().charAt(0);}
			catch(StringIndexOutOfBoundsException e){confirm = 0;}
		}while(confirm != 'y' && confirm != 'Y' && confirm != 'n' && confirm != 'N');
		return (confirm == 'y' || confirm == 'Y');
	}

	/**
	 * Prompts user for entry filename; prevents password file access.
	 */
	private void getFilenameFromUser(){
		filename = "PW";
		while(filename.equalsIgnoreCase("pw")){
			System.out.print("\n\tENTER ENTRY FILENAME AS DATE [mm-dd-yyyy]:   ");
			filename = in.nextLine();
			if(filename.equalsIgnoreCase("pw")) errors.errorMessage("pw", "", "");
		}
		if(filename.equals("")) filename = " ";		
	}

	/**
	 * Gets only the TIME field from the user.
	 * @param timePurpose : the purpose for which time is being asked
	 */
	private void getTimeFromUser(String timePurpose){
		System.out.print("\n\tENTER TIME TO " + timePurpose + " AS [hh:mm]am/pm:   ");
		time = in.nextLine(); 
		if(time.equals("")) time = " ";
	}

	/**
	 * Gets only the PLACE field from the user.
	 */
	private void getPlaceFromUser(){
		System.out.print("\n\tWHERE ARE YOU?   ");
		place = in.nextLine(); 
		if(place.equals("")) place = " ";
	}

	/**
	 * Gets only the MOOD field from the user.
	 */
	private void getMoodFromUser(){
		System.out.print("\n\tHOW ARE YOU FEELING?   ");
		mood = in.nextLine(); 
		if(mood.equals("")) mood = " ";
	}

	/**
	 * Gets only the ENTRY field (entryBody) from the user.
	 */
	private void getEntryBodyFromUser(){
		System.out.print("\n\tENTRY:   ");
		entryBody = in.nextLine(); 
		if(entryBody.equals("")) entryBody = " ";
	}

	/**
	 * Prevents user from adding a time section that already exists.
	 */
	private void validateTime(){
		boolean sectionExists = false;
		do{
			getTimeFromUser("ADD");
			sectionExists = sectionExists();
			if(sectionExists) errors.errorMessage("sectionExists", filename, time);
		}while(sectionExists);
	}

	/**
	 * Determines if user-specified entry already exists
	 * (prevents password file access).
	 * @return true if entry exists; false otherwise
	 */
	private boolean entryExists(){
		file = new File(filename);
		return file.exists();
	}

	/**
	 * Determines if user-specified time section of an entry already exists.
	 * @return true if section exists; false otherwise
	 */
	private boolean sectionExists(){
		Scanner thisFileScan = null;
		try{thisFileScan = new Scanner(file);}
		catch(IOException e){errors.errorMessage("scanner", "", "");}
		while(thisFileScan.hasNext()){
           if(decryptEntry(thisFileScan.nextLine()).equals(time)){
			   thisFileScan.close();
			   return true;
		   }
		   else for(int i = 0; i < 3; i++) thisFileScan.nextLine();
		}
		thisFileScan.close();
		return false;
	}

	/**
	 * Encrypts entry fields before adding to an entry file for security.
	 * @param entryData
	 * @return encryptedEntryData
	 */
	private String encryptEntry(String entryData){
		int length = entryData.length();
    	String encryptedEntryData = "";
		int i = 0;
		while(i != length){
			Character character = entryData.charAt(i);
			int ascii = character + 6;
			encryptedEntryData += (char)ascii;
			i++;
		}
		return encryptedEntryData;
	}

	/**
	 * Decrypts entry fields from an entry file for viewing.
	 * @param encryptedEntryData
	 * @return decryptedEntryData
	 */
	private String decryptEntry(String encryptedEntryData){
		int length = encryptedEntryData.length();
    	String decryptedEntryData = "";
		int i = 0;
		while(i != length){
			Character character = encryptedEntryData.charAt(i);
			int ascii = character - 6;
			decryptedEntryData += (char)ascii;
			i++;
		}
		return decryptedEntryData;
	}
}