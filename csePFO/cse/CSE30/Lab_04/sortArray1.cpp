#include <iostream>
using namespace std;

void sortArr(int isAscending, int arr[], int size)
{
	if(isAscending == 0) //0 to sort array in ascending
	{
		for(int i = size - 1; i > 0; i--) //outer loop decrements everytime a number is placed at end
		{
			int max = arr[0]; //first value and index are temporary "max"
			int maxIndex = 0;

			for(int j = 1; j < i + 1; j++) //inner loop looks through the unsorted values
			{
				if(arr[j] > arr[maxIndex]) //if a number larger than temporary max is found
				{
					max = arr[j]; //larger number becomes new "max"
					maxIndex = j;
				}
			}

			if(maxIndex != i) //if the largest number isn't already at the end
			{
				arr[maxIndex] = arr[i]; //the value at last element is placed where max was
				arr[i] = max; //max is placed at last element
			}
		}
	}

	if(isAscending == 1) //1 to sort array in descending
	{
		for(int i = size - 1; i > 0; i--)
		{
			int min = arr[0]; //only difference is now we use first number as temporary min
			int minIndex = 0;

			for(int j = 1; j < i + 1; j++)
			{
				if(arr[j] < arr[minIndex]) //if a number SMALLER than min is found
				{
					min = arr[j]; //smaller number comes new "min"
					minIndex = j;
				}
			}

			if(minIndex!= i) //if min is not already at end of unsorted array, which "i" represents
			{
				arr[minIndex] = arr[i]; //swap
				arr[i] = min;
			}
		}
	}
}

int main()
{
	int size; //value to pass through as size of array
	int isAscending; //value to pass through as ascending/descending condition

	cout << "Enter the size of the array: ";
	cin >> size;

	if(size > 0) //if size is valid, proceed
	{
		int arr[size];
		cout << "Enter the numbers in the array, seperated by a space, and press enter: ";

		for(int i = 0; i < size; i++) //inputting values for array
		{
			cin >> arr[i];
		}

		cout << "Sort in ascending(0) or descending(1) order? ";
		cin >> isAscending; //0 for ascending, 1 for descending

		sortArr(isAscending, arr, size); //function call to sort array

		if(isAscending == 0) //different output based on whether or not it is ascending/descending
		{
			cout << "This is the sorted array in ascending order: " << endl;
		}
		if(isAscending == 1)
		{
			cout << "This is the sorted array in descending order: " << endl;
		}

		for(int i = 0; i < size; i++) //outputting sorted array
		{
			cout << arr[i] << " ";
		}

		cout << endl; //spacing

	}
	else //else error message occurs
	{
		cout << "ERROR: You entered an incorrect value for the array size!" << endl;
	}

	return 0;
}
