package timeelapsed;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Scanner;

public class TimeElapsed{
	
	// Calculates and writes elapsed times to file using order times file and delivery times file.
	public int timeElapsed(String path1, String path2, String path3, int i) throws IOException{
		// Increment i.
		i++;
		
		// Return this boolean when function completes for displaying doneLabel.
		boolean complete = false;

		// Array for order time = {DD, HH, MM, SS}
		int[] order_time = {0, 0, 0, 0};

		// Array for delivery time = {DD, HH, MM, SS}
		int[] delivery_time = {0, 0, 0, 0};

		// Array for elapsed time = {DD, HH, MM, SS}
		int[] elapsed_time = {0, 0, 0, 0};

		// For getting elapsed time in seconds.
		int total_seconds = 0;

		// Strings to extract times from file (extract_time), 
		// and for formatting result before writing to file (result_time).
		String extract_time = ".";
		String result_time = ".";
		
		// File objects for order times, delivery times, and elapsed times files.
		File filename_order_times = new File(path1);
		File filename_delivery_times = new File(path2);
		File elapsed_times = new File(path3 + "elapsed_times" + i + ".txt");
		while(elapsed_times.exists()){
			i++;
			elapsed_times = new File(path3 + "elapsed_times" + i + ".txt");
		}
		
		// Declare and define Scanners for order times file.
		Scanner file_scan_orders = null;
		try{
			file_scan_orders = new Scanner(filename_order_times);
		}catch(Exception e){e.printStackTrace(); return -1;}
		
		// Declare and define Scanners for delivery times file.
		Scanner file_scan_deliveries = null;
		try{
			file_scan_deliveries = new Scanner(filename_delivery_times);
		}catch(Exception e){e.printStackTrace(); return -1;}
		
		// Declare and define FileWriter for new elapsed time file.
		FileWriter file_writer_elapsed = null;
		try{
			file_writer_elapsed = new FileWriter(elapsed_times, true);
		}catch(IOException e){e.printStackTrace(); return -1;}

		
		/* CALCULATIONS AND FILE WRITING DONE BELOW */


		// While-loop until end of either order or delivery time file.
		while(!extract_time.equals("-1")){

			// Get time of order. If reached end of file, break.
			extract_time = file_scan_orders.nextLine();
			if(extract_time.equals("-1")){
				break;
			}
			order_time[0] = Integer.parseInt(extract_time.substring(0, 2));
			order_time[1] = Integer.parseInt(extract_time.substring(3, 5));
			order_time[2] = Integer.parseInt(extract_time.substring(6, 8));
			order_time[3] = Integer.parseInt(extract_time.substring(9, 11));

			// Get time of delivery. If reached end of file, break.
			extract_time = file_scan_deliveries.nextLine();
			if(extract_time.equals("-1")){
				break;
			}
			delivery_time[0] = Integer.parseInt(extract_time.substring(0, 2));
			delivery_time[1] = Integer.parseInt(extract_time.substring(3, 5));
			delivery_time[2] = Integer.parseInt(extract_time.substring(6, 8));
			delivery_time[3] = Integer.parseInt(extract_time.substring(9, 11));

			// Get total seconds from time of order placement to time of delivery.
			total_seconds = (86400 - order_time[3]) + delivery_time[3];
			elapsed_time[2] = (1440 - order_time[2]) + delivery_time[2];
			total_seconds += (elapsed_time[2] * 60);
			elapsed_time[1] = (24 - order_time[1]) + delivery_time[1];
			total_seconds += (elapsed_time[1] * 3600);

			// Using the total time in seconds, convert to DD HH:MM:SS.
			total_seconds = total_seconds % (24 * 3600);
			elapsed_time[1] = total_seconds / 3600;
			total_seconds %= 3600;
			elapsed_time[2] = total_seconds / 60;
			total_seconds %= 60;
			elapsed_time[3] = total_seconds;

			// Format resulting time with leading zeros and end with newline.
			result_time = String.format("%02d", elapsed_time[0]) 
						+ String.format(" %02d:", elapsed_time[1]) 
						+ String.format("%02d:", elapsed_time[2]) 
						+ String.format("%02d\n", elapsed_time[3]);

			// Print elapsed time to 'elapsed_times.txt'.
			file_writer_elapsed.write(result_time);
		}

		// Close all Scanner objects.
		if(file_scan_orders != null) file_scan_orders.close();
		if(file_scan_deliveries != null) file_scan_deliveries.close();
		
		// Close FileWriter object.
		file_writer_elapsed.close();
		
		return i;
	}
	
	public static void main(String[] args){
		// Initiate program GUI and TimeElapsed object.
		new JFrameForm().setVisible(true);
		new TimeElapsed();
	}
	
}
