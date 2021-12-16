import java.io.*;
import java.util.*;

public class Journal {

	public static void main(String[] args) throws IOException{
		
        // Boolean, validChoice, is used for validating menuChoice.
        boolean validChoice = false;
        
        // Int, exit, used for holding function return value if user chooses to exit program.
        int exit = 0;
        
        // String, menuChoice, used for user-input menu choice.
        char menuChoice = '0';
        
		// Program-specific object declarations for class function use.
		Entry entry = new Entry();
		Password password = new Password();
		
		// Scanner object for user-input.
		Scanner in = new Scanner(System.in);
			
		// Program introduction.
		System.out.println("\n\n  ***************************************");
		System.out.println("  * PASSWORD PROTECTED PERSONAL JOURNAL *");
		System.out.println("  ***************************************");
		
		// ASCII art credit: [n.a.] @ https://www.asciiart.eu/books/books
		System.out.println("\n\n\t (\\"); 
		System.out.println("\t \\'\\"); 
		System.out.println("\t  \\'\\    __________  ");
		System.out.println("\t / ' |  ()_________)");
		System.out.println("\t \\ '/    \\ ~~~~~~~~ \\");
		System.out.println("\t   \\      \\ ~~~~~~   \\");
		System.out.println("\t  (==)     \\__________\\");
		System.out.println("\t  (__)     ()__________)");
		System.out.println();
		
		// Main menu in do-while loop for error-checking.
		do{
			
			// Present main menu, and prompt user for option selection.
			System.out.println("\n\n\t-------------------");
			System.out.println("\t|    MAIN MENU    |");
			System.out.println("\t-------------------");
			System.out.println("\n\tADD\t\t[1]");
			System.out.println("\tVIEW\t\t[2]");
			System.out.println("\tEDIT\t\t[3]");
			System.out.println("\tDELETE\t\t[4]");
			System.out.println("\tPASSWORD\t[5]");
			System.out.println("\tCLOSE JOURNAL\t[6]");
            
		    // Reset validChoice boolean.
            validChoice = false;

            // Do-while loop until valid menu choice is entered.
            do{
                System.out.print("\n\tSELECT OPTION: \t");
                
                try{
                    menuChoice = in.nextLine().charAt(0);
                    if(menuChoice < 49 || menuChoice > 54) ;
                    else validChoice = true;
                }
                catch(StringIndexOutOfBoundsException e){
                    /**/
                }
            }while(!validChoice);

			// Rule-switch for menu options.
			switch(menuChoice){
				case('1') -> exit = entry.addEntry();
				case('2') -> exit = entry.viewEntry();
				case('3') -> exit = entry.editEntry();
				case('4') -> exit = entry.deleteEntry();
				case('5') -> password.editPassword();
                case('6') -> {return;}
				default -> System.out.println("\n\tINVALID OPTION. TRY AGAIN...");
			}
			
			// If user enters 6, close user-input Scanner object, and exit program.
			if(menuChoice == '6' || exit == 1){
				
				// ASCII art credit: [dc] @ https://www.asciiart.eu/art-and-design/borders
				System.out.println("\n\n\t   _____________");
				System.out.println("\t /  \\           \\");
				System.out.println("\t|   |            |");
				System.out.println("\t \\_ |  UNTIL     |");
				System.out.println("\t    |    NEXT    |");
				System.out.println("\t    |      TIME  |");
				System.out.println("\t    |            |");
				System.out.println("\t    |   _________|___");
				System.out.println("\t    |  /            /");
				System.out.println("\t    \\_/____________/");
				System.out.println("\n");

				// Close user-input Scanner object and exit program.
				in.close();
				return;
			}
		}while(menuChoice == '1' || menuChoice == '2' || menuChoice == '3' || menuChoice == '4' || menuChoice == '5');
	}
}
