//By David Wang

import java.util.Scanner;

public class remainderFunc {
	
	public static void main(String[] args)
	{
	
	int max;	//declaring variables
	int divisor;	
	int result;
	
	Scanner input = new Scanner(System.in); 			//input
	
	
	System.out.print("Please enter the max number: ");	//asking for max
	
	max = input.nextInt();									//assigning input into max
	
	System.out.print("Please enter the divisor: ");		//asking for divisor
	
	divisor = input.nextInt();								//assigning input into divisor
	
	for(int i = 1; i <= max; i++)							//for loop to increment i and % by divisor
	{
	
	result = i % divisor;                                   //different result calculated each time i goes up
	
	System.out.println("Num: " + i + " % " + divisor + " = " + result); //Printing Num: i % divisor = result
	
	}
	
	return;
	}
}

//Collaborated with Haoxian Huang