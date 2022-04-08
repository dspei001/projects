import java.util.Scanner;

/**
 * Menus class displays main and sub menus with input validation and
 * redirects user to selected journal operations;
 * NOTE: The functions in this class are listed in 2 groups,
 *		 "MENU FUNCTIONS" and "UTILITIES", where "MENU FUNCTIONS"
 *		 performs the expected operations based on the program menu,
 *		 and where "UTILITIES" functions assist the "MENU FUNCTIONS".
 * @author Debra-Lee Speight
 */
public class Menus{
	private final Entry entry;
	private final Password password;
	private final Scanner in;
	private int mainMenuChoice;
	private int addMenuChoice;
	private int viewMenuChoice;
	private int editMenuChoice;
	private int deleteMenuChoice;

	/**
	 * Constructor instantiates class members.
	 */
	Menus(){
		entry = new Entry();
		password = new Password();
		in = new Scanner(System.in);
		mainMenuChoice = 0;
		addMenuChoice = 0;
		viewMenuChoice = 0;
		editMenuChoice = 0;
		deleteMenuChoice = 0;
	}


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
		mainMenuChoice = 0;
		System.out.println("\n\n\t###################");
		System.out.println("\t#    MAIN MENU    #");
		System.out.println("\t###################");
		System.out.println("\n\tADD\t\t[1]");
		System.out.println("\tVIEW\t\t[2]");
		System.out.println("\tEDIT\t\t[3]");
		System.out.println("\tDELETE\t\t[4]");
		System.out.println("\tRESET PASSWORD\t[5]");
		System.out.println("\tCLOSE JOURNAL\t[6]");

		mainMenuChoice = ensureChoiceWithinBoundary(49, 54);
		if(mainMenuChoice == 49){
			if(displayAddMenuAndRedirect() == 52) return 54;
		}
		else if(mainMenuChoice == 50){
			if(displayViewMenuAndRedirect() == 52) return 54;
		}
		else if(mainMenuChoice == 51){
			if(displayEditMenuAndRedirect() == 52) return 54;
		}
		else if(mainMenuChoice == 52){
			if(displayDeleteMenuAndRedirect() == 52) return 54;
		}
		else if(mainMenuChoice == 53) password.resetPW();
		return mainMenuChoice;
	}

	/**
	 * Displays "ADD" sub-menu on loop with input validation until the
	 * option to go back to "MAIN" menu is selected (addMenuChoice = 3)
	 * or the option to close journal is selected (addMenuChoice = 4).
	 * @return addMenuChoice
	 */
	int displayAddMenuAndRedirect(){
		int addAnother = 0, addCount = 0;
		do{
			addMenuChoice = 0;
			System.out.println("\n\n\t************");
			System.out.println("\t* ADD MENU *");
			System.out.println("\t************");
			System.out.println("\n\tAdd new entry\t\t[1]");
			System.out.println("\tAdd to existing entry\t[2]");
			System.out.println("\tBack to main menu\t[3]");
			System.out.println("\tClose journal\t\t[4]");

			addMenuChoice = ensureChoiceWithinBoundary(49, 52);
			if(addMenuChoice == 49) addCount += entry.addNewEntry();
			else if(addMenuChoice == 50) addCount += entry.addToExisting();
			else if(addMenuChoice == 51 || addMenuChoice == 52) break;

			System.out.print("\n\tAdd another? (Y/N)  ");
			try{addAnother = in.nextLine().charAt(0);}
			catch(StringIndexOutOfBoundsException e){}
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
		int viewAnother = 0;
		if(password.validatePW()){
			do{
				viewMenuChoice = 0;
				System.out.println("\n\n\t*************");
				System.out.println("\t* VIEW MENU *");
				System.out.println("\t*************");
				System.out.println("\n\tView whole entry\t[1]");
				System.out.println("\tView entry section\t[2]");
				System.out.println("\tBack to main menu\t[3]");
				System.out.println("\tClose journal\t\t[4]");

				viewMenuChoice = ensureChoiceWithinBoundary(49, 52);
				if(viewMenuChoice == 49) entry.viewEntry();
				else if(viewMenuChoice == 50) entry.viewSection();
				else if(viewMenuChoice == 51 || viewMenuChoice == 52) break;

				System.out.print("\n\tView another? (Y/N)  ");
				try{viewAnother = in.nextLine().charAt(0);}
				catch(StringIndexOutOfBoundsException e){}
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
		int editAnother = 0, editCount = 0;
		if(password.validatePW()){
			do{
				editMenuChoice = 0;
				System.out.println("\n\n\t*************");
				System.out.println("\t* EDIT MENU *");
				System.out.println("\t*************");
				System.out.println("\n\tEdit whole section of entry\t[1]");
				System.out.println("\tEdit one section field\t\t[2]");
				System.out.println("\tBack to main menu\t\t[3]");
				System.out.println("\tClose journal\t\t\t[4]");

				editMenuChoice = ensureChoiceWithinBoundary(49, 52);
				if(editMenuChoice == 49) editCount += entry.editSection();
				else if(editMenuChoice == 50) editCount += entry.editSectionField();
				else if(editMenuChoice == 51 || editMenuChoice == 52) break;

				System.out.print("\n\tEdit another? (Y/N)  ");
				try{editAnother = in.nextLine().charAt(0);}
				catch(StringIndexOutOfBoundsException e){}
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
		int deleteAnother = 0, deleteCount = 0;
		if(password.validatePW()){
			do{
				deleteMenuChoice = 0;
				System.out.println("\n\n\t***************");
				System.out.println("\t* DELETE MENU *");
				System.out.println("\t***************");
				System.out.println("\n\tDelete whole entry\t[1]");
				System.out.println("\tDelete entry section\t[2]");
				System.out.println("\tBack to main menu\t[3]");
				System.out.println("\tClose journal\t\t[4]");

				deleteMenuChoice = ensureChoiceWithinBoundary(49, 52);
				if(deleteMenuChoice == 49) deleteCount += entry.deleteEntry();
				else if(deleteMenuChoice == 50) deleteCount += entry.deleteSection();
				else if(deleteMenuChoice == 51 || deleteMenuChoice == 52) break;

				System.out.print("\n\tDelete another? (Y/N)  ");
				try{deleteAnother = in.nextLine().charAt(0);}
				catch(StringIndexOutOfBoundsException e){}
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
	 * @return menuChoice
	 */
	int ensureChoiceWithinBoundary(int lowerLimit, int upperLimit){
		int menuChoice = 0;
		while(menuChoice < lowerLimit || menuChoice > upperLimit){
			System.out.print("\n\tSELECT OPTION: \t");
			try{menuChoice = in.nextLine().charAt(0);}
			catch(StringIndexOutOfBoundsException e){}
		}
		return menuChoice;
	}

	/**
	 * Displays the number of successful adds performed.
	 * @param addCount
	 */
	private void displayAddCount(int addCount){
		if(addCount > 0){
			System.out.print("\n\t(" + addCount + ") SUCCESSFULLY CREATED SECTION");
			if(addCount > 1) System.out.print("S");
			System.out.println();
		}
		else System.out.println("\n\tNO SECTIONS CREATED");
	}

	/**
	 * Displays the number of successful edits performed.
	 * @param editCount
	 */
	private void displayEditCount(int editCount){
		if(editCount > 0){
			System.out.print("\n\t(" + editCount + ") SUCCESSFUL EDIT");
			if(editCount > 1) System.out.print("S");
			System.out.println();
		}
		else System.out.println("\n\tNO EDITS PERFORMED");
	}

	/**
	 * Displays the number of successful deletions performed.
	 * @param deleteCount
	 */
	private void displayDeleteCount(int deleteCount){
		if(deleteCount > 0){
			System.out.print("\n\t(" + deleteCount + ") SUCCESSFUL DELETION");
			if(deleteCount > 1) System.out.print("S");
			System.out.println();
		}
		else System.out.println("\n\tNO DELETIONS PERFORMED...");
	}
}