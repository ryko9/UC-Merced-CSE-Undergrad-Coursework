package recursion;

public class Halved {

	// Return the result of dividing n by 2,
	//   ignoring any fractional parts that result.
	// For example, halved(6) and halved(7) should both return 3.
	// Assume n will not be negative.
	public int halved (int n) {
		// fill in the test for the conditional below,
		//  but don't change anything else!
		if (n <= 1) {
			return 0;
		} else {
			return (1 + halved(n-2));
		}
	}

	
}
