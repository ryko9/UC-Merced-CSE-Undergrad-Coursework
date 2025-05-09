#include <iostream>
using namespace std;

int main()
{
	int size; //size of array
	int swaps = 0; //number of swaps

	cout <<  "Enter the size of the array: ";
	cin >> size;

	if(size > 0) //if input is valid
	{
		int arr[size];
		cout << "Enter the numbers in the array, seperated by a space, and press enter: ";

		for(int i = 0; i < size; i++) //inputting values into array
		{
			cin >> arr[i];
		}

		for(int i = size - 1; i > 0; i--) //number of unsorted values in array, decreases everytime "min" is placed at end
		{
			int min = arr[0]; //now, we are assuming the first element is last
			int index = 0;  //index of min

			for(int j = 1; j <= i; j++)  //cycles from j = 1 to i, which represents unsorted elements 
			{
				if(arr[j] < arr[index])
				{
					min = arr[j]; //everytime a smaller umber is found, assigned to min until we get the smallest overall number
					index = j;
				}
			}

			if (index != i) //if the last elmement of array isn't already the smallest, then swap
			{
				swaps++;
				arr[index] = arr[i]; //first assigns the last element to element at index
				arr[i] = min; //then assigns min to the last element of array
			}
		}

		cout << "This is the sorted array in a descending order: ";

		for(int i = 0; i < size; i++) //printing out array contents
		{
			cout << arr[i] << " ";
		}
		cout << endl; //spacing for clarity

		cout << "The algorithm selected the minimum for the traverse of the array." << endl;
		cout << "It took " << swaps << " swaps to sort the array..." << endl; //displaying number of swaps.
	}
	else //if size is invalid
	{
		cout << "ERROR: You entered an incorrect value for the array size!" << endl;
	}
	return 0;
}
