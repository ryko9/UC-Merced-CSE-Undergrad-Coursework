package project1;

import java.util.*;

public class Shop 
{
	private static int numItems = 0; //number of items in menu
	private static double discAmount = 0; //amount spent to qualify for a discount;
	private static double discRate = 0; //discount rate
	
	private static boolean setup = false;
	private static boolean buy = false;
	
	private static String[] names; //array to store names of products
	private static double[] prices; //array to store prices of products
	private static int[] numBought; //array to store number of items purchased per product type
	
private static void setup(Scanner input) //I Setup
{
	System.out.print("Please enter the number of items: ");
	numItems = input.nextInt();
	names = new String[numItems]; //initializing name array to have appropriate spaces according to number of items
	prices = new double[numItems]; //initializing price array
	numBought = new int[numItems];
	
	for (int i = 0; i < numItems; i++) //loop to assign values to string and name arrays
	{
		System.out.print("Enter name of product " + i + ": ");
		names[i] = input.next();
		System.out.print("Enter price of product " + i + ": ");
		prices[i] = input.nextDouble();
	}	
	
	System.out.print("Please enter the amount to qualify for discount: ");
	discAmount = input.nextDouble();
	System.out.print("Please enter the discount rate(0.1 for 10%): ");
	discRate = input.nextDouble();	

	setup = true; //setup is done.
}

private static void buy(Scanner input) //II Buy
{
	if (setup == true) //only works if set up has been done
	{
		for(int i = 0; i < numItems; i++)
		{
			System.out.print("Enter the amount of " + names[i] + " : ");
			numBought[i] = input.nextInt();
		}
		
		buy = true; //buy is done
	}
	else
	{
		System.out.println(" "); //spacing for clarity
		System.out.println("Shop is not setup yet!");
		System.out.println(" ");
	}
	
}

private static void list() //III List
{
	if(setup == true && buy == true) //if user has setup shop and bought
	{
		for (int i = 0; i < numItems; i++)
		{
			if(numBought[i] != 0) //if there are 0 items, doesnt display.
			{
				System.out.println(numBought[i] + " count(s) of " + names[i] + " @ " + prices[i] + " = $" + (prices[i] * numBought[i])); //price[i] * numBought[i] = The price of the item times the quantity bought
			}
		}
	}
	else if(setup == true)
	{
		System.out.println(" ");
		System.out.println("Try again: You have not bought anything");
		System.out.println(" ");
	}
	else
	{
		System.out.println(" ");
		System.out.println("Shop is not setup yet!");
		System.out.println(" ");
	}
}

private static void checkout() //IV Checkout
{
	double sub = calcSubTotal(); //subtotal, doesn't include discounted amount
	double discount = calcDiscount(); //amount discounted
	double total = sub - discount;  //actual total, subtotal - discounted amount
	
	if (setup == true && buy == true)
	{
		System.out.println("Thanks for coming!");
		System.out.println("Sub Total: $" + sub);
		System.out.println("Discount: $" + discount);
		System.out.println("Total: $" + total); 
	}
	else if (setup == true)
	{
		System.out.println(" ");
		System.out.println("Try again: You have not bought anything");
		System.out.println(" ");
	}
	else
	{
		System.out.println(" ");
		System.out.println("Shop is not setup yet!");
		System.out.println(" ");
	}

}

private static double calcSubTotal() //calculates total not counting discount
{
	double total = 0;
	for (int i = 0; i < numItems; i++)
	{
		total += prices[i] * numBought[i]; //multiplies the price of the item times the quantity of the item bought, which the two arrays represent. adds them all up for total.
	}
	
	return total;
}

private static double calcDiscount() //calculates amount discounted, if eligible
{
	double discTotal = 0; //cost discounted
	if (calcSubTotal() >= discAmount) //if the subtotal meets requirement for discount
	{
		discTotal = calcSubTotal() * discRate;
	}
	return discTotal;
}

private static void run(Scanner input) //uses all the methods depending on user input
{
	System.out.println("This program supports 4 functions:");
	System.out.println("      1. Setup Shop");
	System.out.println("      2. Buy");
	System.out.println("      3. List Items");
	System.out.println("      4. Checkout");
	
	System.out.print("Please choose the function you want: ");
	int function = input.nextInt(); //user selected function number
	
	if(function == 1)
	{
		setup(input);
		run(input);
	}
	else if(function == 2)
	{
		buy(input);
		run(input);
	}
	else if(function == 3)
	{
		list();
		run(input);
	}
	else if(function == 4)
	{
		checkout();
	}
	else
	{
		System.out.println("Error: Do not know " + function);
		run(input);
	}
}

public static void main(String[] args)
{
	Scanner input = new Scanner(System.in);
	run(input);
}

}