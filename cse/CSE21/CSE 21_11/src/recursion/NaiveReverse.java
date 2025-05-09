package recursion;

/* Some naive solutions to reverse a string.     You should write reverse6 below.
 *
 * Reminder: s.substring(n1,n2) returns the string that starts at position n1
 * and ends at position n2-1.  For example, if s contains the string "abcde",
 * s.substring(1,4) returns "bcd".
 */
public class NaiveReverse {

	// returns the reverse of a one-length string.  Easy!
	public String reverse1 (String s) {
		return s;
	}
	
	//returns the reverse of a two-length string.
	public String reverse2 (String s) {
		return (s.substring(1,2) + s.substring(0,1));
	}
	
	//returns the reverse of a three-length string.
	public String reverse3 (String s) {
		return (s.substring(2,3) + s.substring(1,2) + s.substring(0,1));
	}
	
	// ... reverse4 and reverse5 would be similar
	
	// WRITE reverse6, which takes a String of length 6 and returns its reverse
	// Don't use while or for loops!
	public String reverse6 (String s) {
		return(s.substring(5,6) + s.substring(4,5) + s.substring(3,4) + s.substring(2,3) + s.substring(1,2) + s.substring(0,1));
	}
	

	
	// ... and more could go here... reverse612() would be awfully long...	

}
