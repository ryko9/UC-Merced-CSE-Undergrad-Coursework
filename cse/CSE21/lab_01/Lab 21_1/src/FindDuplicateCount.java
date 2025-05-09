//by David Wang

public class FindDuplicateCount {

	public static void main(String[] args) 
	{
		int[] arr = {1, 2, 2, 3, 4, 2, 4, 3, 0, 5, 3, 2};
				
		for (int i = 0; i < arr.length; i++)			//cycling through array
		{
			int numRepeat = 0;							//numRepeat is set to zero every time the loop goes to a different number
			
			for (int k = i + 1; k < arr.length; k++)	//cycling through number next to i to look for repeats
			{
				
				if(arr[k] == arr[i])
				{
				numRepeat++;							//every time there is a repeat, the count increases by 1
				}
				
			}

			/*After cycling through all the array values to check if there are repeats and appropriately counting the number of repeats, different outputs are given based on
			 * the repeat value.
			 */
		
			if (numRepeat > 1)																									   //if there are more than one repeats
			{
				System.out.println("There are " + numRepeat + " more occurences of value " + arr[i] + " starting at index " + i); 
			}
			else if(numRepeat == 1)																								   //if there is only one repeat
			{
				System.out.println("There is only 1 or more occurence of value " + arr[i] + " starting at index " + i);
			}
			else																												   //no repeats
			{
				System.out.println("No duplicates with value " + arr[i] + " beyond Index " + i);
			}
		}
		
		
		
		
		return;
	}

}


//Collaborated with Haoxian Huang 