#include <iostream>
using namespace std;

int main()
{
	int size; //user inputted size for rows and columns of 2d array
	int input; //variable to store element input, need it to check if negative
	int negativeCount = 0; //used to count negatives

	cout << "Enter the size of a 2D array: ";
	cin >> size;

	if(size > 0 && size <= 10) //if user input for size is within 1-10, proceed
	{
		int arr[size][size]; //2d array with same amount of columns and rows, since it is a square

		for(int i = 0; i < size; i++) //incrementing through rows
		{
			cout << "Enter the array for row " << (i + 1) << " seperated by a space, and press enter: ";

			for(int j = 0; j < size; j++) //incrementing through columns
			{
				cin >> input;
				arr[i][j] = input;

				if(input < 0) //if input is less than 0, add to negativeCount
				{
					negativeCount++;
				}
			}
		}

		if(negativeCount > 0) //if there are any negatives
		{
			cout << "There are " << negativeCount << " negative values!" << endl; //displaying number of negatives
		}
		else //if there are no negatives
		{
			cout << "All values are non-negative!" << endl;
		}
	}
	else if(size > 10) //if size is over 10
	{
		cout << "ERROR: Your array is too large! Enter 1 to 10." << endl;
	}
	else //if size is negative, or invalid
	{
		cout << "ERROR: you entered an incorrect value for the array size!" << endl;
	}

	return 0;
}
