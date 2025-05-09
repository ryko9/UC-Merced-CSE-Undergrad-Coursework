package oop;


/**
 * A counter class that cycles its internal value back to 0 when it
 * reaches a maximum value. 
 * 
 * e.g., A (new) ModNCounter with a cycleLength (maximum) of 5 will,
 * when increment() is called 7 times, have an internal value of 2
 */
public class ModNCounter  extends Counter { 

	
    private int cycleLength; 

    public ModNCounter (int n) { 
    	cycleLength = n; 
    }  

    
    public void increment ( ) { 
    	// fill in this method such that value() will return
    	//  the correct value
    		super.increment(); 
    		if(super.value() == (cycleLength))
    		{
    			super.reset();
    		}
    } 
} 