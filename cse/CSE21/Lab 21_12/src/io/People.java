package io;

import java.util.*;
import java.io.*;

public class People {
	
	public ArrayList<Person> readFile() {
		// this version asks for the file
		System.out.print("Enter the file name: ");
		Scanner kbd = new Scanner(System.in);
		String filename = kbd.next();
		return readFile(filename);
	}
	
	
	public ArrayList<Person> readFile(String filename) {
		// create people array
		ArrayList<Person> people = new ArrayList<Person>();
		
		try {
			Scanner input = new Scanner ( new FileReader(filename) );
			while (input.hasNextLine()) {
				
				/*
				 * Fill-in .. Do not touch the rest of the code
				 */ 
				input.useDelimiter("[\t\r]");  //splits string up into sections after tabs
				
				people.add(new Person(input.next(), input.nextInt(), input.nextLine().trim())); //adds new person with arguments, (name, age, location)
				// end of code to be filled in
			} 
			input.close();
		} catch ( NoSuchElementException e){
			System.out.println(e); 
			
		} catch (FileNotFoundException e) {
			System.out.println(e);
		}
		return people;
	}

	
	public void printPeople(ArrayList<Person> people) {
		for (Person p : people) {
			System.out.println(p);
		}
	}
	
	
}
