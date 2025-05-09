import java.util.*;

public class Lab21_Vars {

	public static void main(String[] args) {

		int i = 0, j = 0;
		int var0, var1;
		
		// Q1 : Fix, typecast 5.0 to an int so it can be used for var3
		int var2 = 0, var3 = (int)5.0;
		
		// Q2 : Fix - declare the variable as an array 
		int[] arri0 = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
		
		double[] arrd0 = {0.0, 1.0, 2.0, 3.0, 4.0};
		
		// Q3 : Fix what's wrong with temp?
		int temp;
		if (i < j) {
			temp = 0;
			System.out.println("Temp is " + temp);
		} else {
			temp = 1;
			System.out.println("Temp is " + temp);
		}
		
		// Q4-5 : Fix it should calculate sum squared and print it as total
		int total = 0;
		for (i = 0; i < 10; i++) {
			total = 0;
			total += i*i;
		}
		System.out.println("i value is " + i);
		System.out.println("Total is " + total);
		
		// Q6-7 : Fix Logical Error
		Cheese jack = new Cheese();
		Cheese monterey = new Cheese("Monterey");
		System.out.println("Monterey name is " + monterey.getName());
		jack.setName("Jack");
		System.out.println("Jack name is " + jack.getName());
		System.out.println("Monterey name is still " + monterey.getName());
	
		// Q8-9 Make this shorter by combining dedundant statements
		Scanner input = new Scanner(System.in);
		System.out.print("Enter first number: ");
		int num1 = input.nextInt();
		System.out.print("Enter second number: ");
		int num2 = input.nextInt();
		
		if (num1 > var3) 
		{
			System.out.println("First is greater");
			
			if (num2 < var3)
				System.out.println("Second is Less than");
			else
				System.out.println("Second is Greater or equal");
		} 
		
		else 
		{
			System.out.println("First is Less than or equal");
			
			if (num2 < var3)
				System.out.println("Second is Less than");
			else
				System.out.println("Second is Greater or equal");
			
		}

// Q9 : Print out the first number entered by the user
//      Hint : You will need to modify the above code
		
		System.out.println(num1);
		
	}

}
