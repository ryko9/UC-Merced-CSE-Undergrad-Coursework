#include <iostream>
using namespace std;

int main()
{
	int size; //size of array

	cout << "Enter the size of the array: ";
	cin >> size;

	if(size > 0) //if input is valid
	{
		int arr[size]; //initializing array
		cout << "Enter the numbers in the array, seperated by a space, and press enter: ";

		for (int i = 0; i < size; i++) //inputting values into array
		{
			cin >> arr[i];
		}

		for (int i = size - 1; i > 0; i--) // "i" represents the index of last element of unsorted array. decreases by 1 everytime "max" is placed at the end, since that number is now sorted
		{
			int max = arr[0];
			int index = 0;

			for(int j = 1; j <= i; j++) //goes through the unsorted elements and places largest at end. the size of unsorted array is i.
			{
				//j starts from 1 since element 0 is used as temporary "max". goes up to i since array size shrinks when max is sorted out
				if (arr[j] > arr[index])
				{
					max = arr[j];  //everytime a larger number is found, it becomes "max"
					index = j;   //the index of the new "max".
				}
			}

			if(index != i) //if the index of "max" is not the same as "i", swaps max with the last element
			{
				arr[index] = arr[i]; //first, max becomes the last element
				arr[i] = max; //then, last element becomes the largest number, which was stored in "max".

			}
		}

		cout << "This is the sorter array in ascending order: ";
		for(int i = 0; i < size; i++) //cycling through sorted array to print it out
		{
			cout << arr[i] << " ";
		}
		cout << endl;
		cout << "The algorithm selected the maximum for the traverse of the array." << endl;

	}
	else //if size is invalid
	{
		cout << "ERROR: You entered an incorrect value for the array size!" << endl;
	}


return 0;
}
