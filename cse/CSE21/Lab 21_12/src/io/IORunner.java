package io;

import java.util.ArrayList;

public class IORunner {

	
	public static void main(String[] args) {
		// edit as necessary
		//testPeople();
		
		testPhoneNumbers();
		testPeople();
	}
	

	
	
	public static void testPeople() {
		// fill in as necessary		
		People p = new People();
		
		ArrayList<Person> people = p.readFile(); //since readfile returns arraylist
		
		for(int i = 0; i < people.size(); i++)
		{
			if(i == 15)  //since theres a random space in the output in the lab instructions, I tried to match it.
			{
				System.out.println(); 
			} 
			
			System.out.println(people.get(i));
		}
		System.out.println("Total is " + people.size());
	}
	
	public static void testPhoneNumbers() //testing PhoneNums.java
	{
		PhoneNums nums = new PhoneNums();
		nums.readPhoneNumbers();
	}


	
}
