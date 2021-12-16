import java.io.*;
import java.util.*;

public class Password {
	
	public int password(){
		
		// Inform user of three attempts to enter correct password.
		System.out.println("\n\t.:: FOR SECURITY REASONS, ONLY 3 ATTEMPTS ARE ALLOWED ::.");
		
		// Strings to hold user-entered password and decrypted saved password.
		String passwordEntered = "", decryptedPassword = "";
		
		// Local object declarations for class function use.
		Errors errors = new Errors();
		Entry entry = new Entry();
		
		// Scanner object for user input.
		Scanner in = new Scanner(System.in);

		// File object for password file.
		File file = new File("PW");
			 
		// File Scanner object for password file. 
		Scanner fileScan = null;
			
		// If file does not exist... 
		if(!file.exists()){

			// ...display default password to user
			errors.errorMessage("pwu", "");

			// ...create new password file
			try{
				file.createNewFile();
			}
			catch(IOException e){
				errors.errorMessage("write", "");
				//e.printStackTrace();
			}

			// ...and write the default password to password file after encrypting.
			try{
				FileWriter fileWriter = new FileWriter(file);
				String defaultPW = entry.encryptDecrypt(" ", true, false);
				fileWriter.write(defaultPW);
				fileWriter.close();
			}
			catch(IOException e){
				errors.errorMessage("write", "");
				//e.printStackTrace();
			}
		}
		
		// Set file Scanner object.
		try{
			fileScan = new Scanner(file);
		}
		catch(IOException e){
			errors.errorMessage("write", "");
			//e.printStackTrace();
		}

		// Get the password from the password file and decrypt.
		decryptedPassword = fileScan.nextLine();
		decryptedPassword = entry.encryptDecrypt(decryptedPassword, false, true);

		// Close file scanner object.
		fileScan.close();
			
		// For-loop for the three attempts.
		for(int i = 0; i < 3; i++){

			// Prompt user to enter password.
			System.out.print("\n\tENTER CURRENT PASSWORD:  ");
			passwordEntered = in.nextLine();

			// If user-entered password matches decrypted password, access granted; return.
			if(passwordEntered.equals(decryptedPassword)){
				System.out.println("\n\tACCESS GRANTED...");
				return 0;
			}

			// Else, display message for invalid password.
			else System.out.println("\n\tINVALID PASSWORD...");
		}

		// If three failed attempts have been made, display message and return 1.
		System.out.println("\n\t.:: YOU HAVE REACHED THE MAXIMUM ATTEMPTS ALLOWED. ACCESS DENIED ::.");
		return 1;
	}
	
	public void editPassword(){
		
		// Boolean to determine whether password is confirmed.
		boolean passwordConfirmed = false;
		
		// Int variable, checkPassword, holds return value of password().
		int checkPassword = 0;
		
		// Strings to hold new password and decrypted saved password.
		String newPassword = "", confirmNewPassword = "";
		
		// Local object declarations for class function use.
		Errors errors = new Errors();
		Entry entry = new Entry();
		
		// Scanner object for user input.
		Scanner in = new Scanner(System.in);

		// Introduce 'edit password' section.
		System.out.println("\n\n\t*****************");
		System.out.println("\t* EDIT PASSWORD *");
		System.out.print("\t*****************\n");

		// Check user password. password() returns 0 if correct password and returns 1 if incorrect password.
		checkPassword = password();

		// If password is incorrect, return to main menu.
		if(checkPassword == 1) return;
			
		// Do-while loop until new password confirmation is successful.
		do{

			// Prompt user to enter new password.
			System.out.print("\n\tENTER NEW PASSWORD:  ");
			newPassword = in.nextLine();

			// Prompt user to confirm new password.
			System.out.print("\tCONFIRM NEW PASSWORD:  ");
			confirmNewPassword = in.nextLine();

			// If the two passwords match...
			if(newPassword.equals(confirmNewPassword)){

				// ...open password file for writing using PrintWriter object
				PrintWriter printWriter = null;

				try{
					printWriter = new PrintWriter("PW");
				}
				catch(FileNotFoundException e){
					errors.errorMessage("write", "");
					//e.printStackTrace();
				}

				// ...write new encryoted password to password file
				printWriter.print("");
				newPassword = entry.encryptDecrypt(newPassword, true, false);
				printWriter.print(newPassword);
				
				// ...and close PrintWriter object.
				printWriter.close();

				// Passwords match, so password is confirmed; exits do-while loop.
				passwordConfirmed = true;
			}

			// Else, if password editing is unsuccessful, display message.
			else System.out.print("\n\tTHE PASSWORDS DO NOT MATCH. TRY AGAIN...");

		}while(!passwordConfirmed);

		// If password edit is successful, display message and return to main menu.
		System.out.println("\n\tPASSWORD SUCCESSFULLY CHANGED...");
	}
}
