/**
 * Errors class provides the appropriate error message upon program error.
 * @author Debra-Lee Speight
 */
public class Errors{
	protected int errorMessage(String type, String filename, String section){
		switch(type){
			case "create" -> {
				System.out.print("\n\t(!) NEW FILE ERROR:");
				System.out.println(" Error creating new entry [" + filename + "].");
			}
			case "filewriter" -> {
				System.out.print("\n\t(!) FILEWRITER ERROR:");
				System.out.println(" Error writing to entry [" + filename + "].");
			}
			case "scanner" -> {
				System.out.print("\n\t(!) SCANNER ERROR:");
				System.out.println(" Error scanning entry [" + filename + "].");
			}
			case "section" -> {
				System.out.print("\n\t(!) ERROR: Section [" + section + "]");
				System.out.println(" does not exist in entry [" + filename + "].");
			}
			case "file" -> {
				System.out.print("\n\t(!) ERROR:");
				System.out.println(" Entry [" + filename + "] does not exist.");
			}
			case "fileExists" -> {
				System.out.println("\n\t(!) ERROR: Entry [" + filename + "] already exists.");
			}
			case "sectionExists" -> {
				System.out.print("\n\t(!) ERROR: Section [" + section + "] already exists");
				System.out.println(" in entry [" + filename + "].");
			}
			case "defaultPW" -> {
				System.out.print("\n\t(!) ALERT: Default password is currently set.");
				System.out.print("\n\t           ");
				System.out.println("Select RESET PASSWORD from main menu to change it.");
			}
			case "pw" -> {
				System.out.print("\n\t(!) ERROR:");
				System.out.println(" ACCESS TO PASSWORD FILE DENIED!");
			}
			default -> {}
		}
		return 1;
	}
}
