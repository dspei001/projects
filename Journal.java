/**
 * Journal class displays intro message, menu options, and exit message.
 * @author Debra-Lee Speight
 */
public class Journal{
	public static void main(String[] args){
		Menus menus = new Menus();
		int menuChoice = 0;

		displayIntro();

		// While menu choice does not equal 6 (where 6 = "CLOSE JOURNAL").
		while(menuChoice < 54) menuChoice = menus.displayMainMenu();

		displayExit();
	}

	/**
	 * Displays introduction.
	 * @credit (journal ASCII art): [n.a.] @ https://www.asciiart.eu/books/books
	 */
	public static void displayIntro(){
		System.out.println("\n\n    ############################");
		System.out.println("    #    PASSWORD PROTECTED    #");
		System.out.println("    #     PERSONAL JOURNAL     #");
		System.out.println("    ############################");
		System.out.println("\n\n\t(\\"); 
		System.out.println("\t\\'\\"); 
		System.out.println("\t \\'\\    __________  ");
		System.out.println("\t/ ' |  ()_________)");
		System.out.println("\t\\ '/    \\ ~~~~~~~~ \\");
		System.out.println("\t  \\      \\ ~~~~~~   \\");
		System.out.println("\t (==)     \\__________\\");
		System.out.println("\t (__)     ()__________)");
		System.out.println();
	}

	/**
	 * Displays exit message.
	 * @credit (paper ASCII art): [dc] @ https://www.asciiart.eu/art-and-design/borders
	 */
	public static void displayExit(){
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
	}
}