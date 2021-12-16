import java.util.*;

public class Errors {
	
	protected int errorMessage(String type, String filename){

		// Scanner object for user input.
		Scanner in = new Scanner(System.in);
	
		// Rule-switch for error type.
		switch(type){
			
			// Error creating or writing to file.
			case "write" -> System.out.println("\n\t(!) SYSTEM ERROR...");
		
			// Error reading or opening file: File does not exist.
			case "read" -> System.out.println("\n\t(!) THE ENTRY [" + filename + "] DOES NOT EXIST...");

			// No current password is set; password is default.
			case "pwu" -> System.out.println("\n\t(!) NO PASSWORD SET: THE CURRENT PASSWORD IS DEFAULT...");

			// Error: Attempting to view password file.
			case "pwv" -> System.out.println("\n\t(!) FATAL ERROR! CANNOT VIEW PASSWORD FILE!");

			// Error: Attempting to edit password file.
			case "pwe" -> System.out.println("\n\t(!) FATAL ERROR! CANNOT EDIT PASSWORD FILE!");
			
			// Error: Attempting to delete password file.
			case "delete" -> System.out.println("\n\t(!) FATAL ERROR! CANNOT DELETE PASSWORD FILE!");

			default -> {}
		}

		return 1;
	}
}
