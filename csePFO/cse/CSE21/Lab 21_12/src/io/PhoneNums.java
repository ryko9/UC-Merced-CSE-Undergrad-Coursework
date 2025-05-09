package io;

import java.util.*;
import java.io.*;

public class PhoneNums {

	public ArrayList<String> readPhoneNumbers() 
	{
		String filename = "data/phone.txt"; 
		ArrayList<String> output = new ArrayList<String>();

		try {
			Scanner input = new Scanner ( new FileReader(filename) );
			while (input.hasNextLine()) {
				
				input.useDelimiter("[+-]");	     //Delimiter splits string up every time there is a '+' or '-'. Storing the different pieces
												 //in strings allows for the .replace() method to be used
				
				String country = input.next();   //since there is dash after country code, country is split from the original number 
				
				String area = input.next(); 	 //since there is a dash after area code, area is split from the original number
												 //(not including the already split country code) 
				
				String number = input.nextLine(); //what remains of the original code after removing country code and area code 
												  //is supposed to be phone number, but some phone numbers have
												  //dashes in them so they will be split into two separate strings unless you use .nextLine()
				
				number = number.replace("-", ""); 
				/*.nextLine() doesn't split the last part of the number up or remove the dashes, so need to manually remove dashes
				through .replace("-", "") */
				
				System.out.println("Country code: " + country); 
				System.out.println("Area code: " + area);
				System.out.println("Phone number: " + number); 
				System.out.println(); //spacing for clarity.
			} 
			input.close();
		} catch ( NoSuchElementException e){
			System.out.println(e);

		} catch (FileNotFoundException e) {
			System.out.println(e);
		}
		
		return output;
		
	}
}