import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Scanner;

/**
 * Password class contains password-related operations such as encrypting,
 * decrypting, validating, and resetting the password file.
 * @author Debra-Lee Speight
 */
public class Password{
	private final Errors errors;
	private final Scanner in;
	private Scanner fileScan;
	private File file;

	/**
	 * Constructor instantiates class members.
	 */
	Password(){
		errors = new Errors();
		in = new Scanner(System.in);
		fileScan = null;
		file = null;
	}

	/**
	 * Allows user to reset password upon validation of current password.
	 */
	void resetPW(){
		String newPW = "newPW", confirmNewPW = "confirmPW";
		boolean oldPWvalidated = validatePW();
		while(oldPWvalidated && !newPW.equals(confirmNewPW)){
			System.out.print("\n\tEnter new password:  ");
			newPW = in.nextLine();

			System.out.print("\tConfirm new password:  ");
			confirmNewPW = in.nextLine();

			if(newPW.equals(confirmNewPW)){
				try{file.createNewFile();}
				catch(IOException e){errors.errorMessage("create", "", "");}

				try{
					FileWriter fileWriter = new FileWriter(file);
					fileWriter.write(encryptPW(newPW));
					fileWriter.close();
				}
				catch(IOException e){errors.errorMessage("filewriter", "", "");}
			}
			else System.out.println("\n\t(!) ERROR: The passwords do not match.");
		}
		System.out.println("\n\tPassword changed successfully.");
	}

	/**
	 * Validates the password by comparing the decrypted password to the user's
	 * password input; user gets 3 attempts to enter the correct password.
	 * @return true if password entered is correct; false otherwise
	 */
	boolean validatePW(){
		String currentPW = getCurrentPW();
		for(int i = 0; i < 3; i++){
			System.out.print("\n\tENTER CURRENT PASSWORD:  ");
			String pwEntered = in.nextLine();

			if(pwEntered.equals(currentPW)){
				System.out.println("\n\tACCESS GRANTED!");
				return true;
			}
			else System.out.println("\n\tINVALID PASSWORD");
		}
		System.out.println("\n\tACCESS DENIED!");
		return false;
	}

	/**
	 * Creates the password file, encrypts and writes the default password
	 * to the password file, and displays the default password to the user.
	 */
	private void setDefaultPW(){
		try{
			FileWriter fileWriter = new FileWriter(file);
			fileWriter.write(encryptPW(" "));
			fileWriter.close();
		}
		catch(IOException e){errors.errorMessage("filewriter", "", "");}
		errors.errorMessage("defaultPW", "", "");
	}

	/**
	 * Opens the password file, then decrypts and returns the password.
	 * @return currentPW decrypted
	 */
	private String getCurrentPW(){
		file = new File("PW");
		if(!file.exists()){
			try{file.createNewFile();}
			catch(IOException e){errors.errorMessage("create", "", "");}
			setDefaultPW();
		}
		try{fileScan = new Scanner(file);}
		catch(IOException e){errors.errorMessage("scanner", "", "");}

		String currentPW = fileScan.nextLine();
		fileScan.close();
		return decryptPW(currentPW);
	}

	/**
	 * Encrypts the password in the password text file for security.
	 * @param pw
	 * @return encryptedPW
	 */
	private String encryptPW(String pw){
		int length = pw.length();
    	String encryptedPW = "";
		int i = 0;
		while(i != length){
			Character character = pw.charAt(i);
			int ascii = character + 12;
			encryptedPW += (char)ascii;
			i++;
		}
		return encryptedPW;
	}

	/**
	 * Decrypts the password in the password text file for validation.
	 * @param encryptedPW
	 * @return decryptedPW
	 */
	private String decryptPW(String encryptedPW){
		int length = encryptedPW.length();
    	String decryptedPW = "";
		int i = 0;
		while(i != length){
			Character character = encryptedPW.charAt(i);
			int ascii = character - 12;
			decryptedPW += (char)ascii;
			i++;
		}
		return decryptedPW;
	}
}