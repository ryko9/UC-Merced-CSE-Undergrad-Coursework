package recursion;

public class Reverse {

	/*
	 * Now, write a recursive solution to reverse without using any helper methods.
	 * That is, reverse should only call reverse! (and some string manipulation methods).
	 */
	
	
	public String reverse (String s) {

		if (s.length() <= 1) {
			// base case
			return s;
			
		} else {
			// the recursive case! 
			
			return reverse(s.substring(1)) + s.charAt(0); // (Puts the first character at the end then calls itself again with the previous string minus the first)
												// reverse("David")
												// reverse("avid") + D
												// reverse("vid") + a + D) .... until you get "divaD"
		}
	}
	
	
	
	//////// HELPER METHODS YOU MIGHT FIND USEFUL
	
	// returns a string containing all the characters except the first
	public static String allButFirst(String s) {
		return s.substring(1);
	}
	
	// returns a string  containing all the characters except the last
	public static String allButLast(String s) {
		return s.substring(0, s.length());
	}	
}
