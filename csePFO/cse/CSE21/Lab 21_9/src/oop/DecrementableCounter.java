package oop;

public class DecrementableCounter extends Counter{
	
	public void decrement()
	{
		if(super.value() != 0)
		{
			int index = super.value(); //original value of myCount needed to determine number of loops
			super.reset(); //myCount value is reset to 0 before incrementing up to myCount - 1.
			for(int i = 0; i < index - 1; i++) //since we dont have access to myCount, can only modify it through increment
			{
				super.increment();
			}
		}
	}
	
}
