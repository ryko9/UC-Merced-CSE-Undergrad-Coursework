package oop;

public class Runner {

	public static void main(String[] args) {
		testCounter();

		testCounter7Statements();

		testModNCounter();
		
		testModNCounter2();
		
		testDecrementableCounter();
		
		testSeasonCounter();
	}

	
	public static void testCounter() {
		System.out.println("-- testing Counter");

		Counter c = new Counter();
		for(int i = 0; i < 3; i++)
		{
			c.increment();
			System.out.println(c.value());
		}
		System.out.println("current value : " + c.value());

	}

	
	// Use this method to complete exercise 1c
	public static void testCounter7Statements() {
		Counter c = new Counter();
		System.out.println("-- testing 7 statements");
		// include exactly 7 increment() and reset() statements below
		
		for(int i = 0; i < 3; i++)
		{
			c.increment();
			System.out.println(c.value());
		}
		c.reset();
		for(int i = 0; i < 3; i++)
		{
			c.increment();
			System.out.println(c.value());
		}

		System.out.println("current value: " + c.value());
	}
	
	public static void testModNCounter()
	{
		Counter c = new ModNCounter(2);
		System.out.println("-- testing ModNCounter");
		
		System.out.println (c.value()); 
		c.increment();
		System.out.println (c.value());
		c.increment();
		System.out.println (c.value());
		
		System.out.println("current value: " + c.value());
	}
	
	public static void testModNCounter2()
	{
		Counter c = new ModNCounter2(2);
		System.out.println("-- testing ModNCounter2");
		
		System.out.println (c.value()); 
		c.increment();
		System.out.println (c.value());
		c.increment();
		System.out.println (c.value());
		
		System.out.println("current value: " + c.value());
	}

	public static void testDecrementableCounter()
	{
		DecrementableCounter c = new DecrementableCounter();
		System.out.println("-- testing DecrementableCounter");
		
		System.out.println(c.value());
		System.out.println("Decrement called.");
		c.decrement();
		System.out.println(c.value());
		System.out.println("Incremented called twice.");
		c.increment();
		c.increment();
		System.out.println(c.value());
		System.out.println("Decrement called.");
		c.decrement();
		System.out.println(c.value());
		System.out.println("Decrement called.");
		c.decrement();
		System.out.println(c.value());
		
		System.out.println("current value: " + c.value());
	}
	
	public static void testSeasonCounter()
	{
		SeasonCounter c = new SeasonCounter();
		System.out.println("-- testing SeasonCounter");
		for(int i = 0; i < 4; i++)
		{
			System.out.println(c.toString());
			c.increment();
			System.out.println("Increment called.");
		}
		System.out.println(c.toString());
		System.out.println("current season: " + c.toString());
	}
}
