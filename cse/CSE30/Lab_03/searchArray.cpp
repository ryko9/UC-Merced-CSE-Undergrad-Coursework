#include <iostream>
using namespace std;

int main()
{
	int size; //size of array
	int index; //index where value was found
	int checks = 0; //number of checks performed
	bool found = false; //becomes true if item is found in array
	int value; //value to find in array

	cout << "Enter the size of the array: ";
	cin >> size;

	if(size > 0) //if input is valid, proceed
	{
		int arr[size];

		cout << "Enter the numbers in the array, seperated by a space, and press enter: ";
		for (int i = 0; i < size; i++) //taking in array input
		{
			cin >> arr[i];
		}

		cout << "Enter a number to search for in the array: ";
		cin >> value;

		for(int i = 0; i < size; i++) //sequential search through array
		{
			checks++;
			if(arr[i] == value)
			{
				found = true;
				index = i; //index at which item was found
				break;
			}
		}
	if(found == true) //if item was found in array
	{
		cout << "Found value " << value << " at index " << index << ", which took " << checks << " checks." << endl;
		if(index == 0) //best case value was found at first index
		{
			cout << "We ran into the best case scenario!" << endl;
		}
		if(index == size - 1) //worst case value was found at last index
		{
			cout << "We ran in to the worst case scenario!" << endl;
		}
	}
	else
	{
		cout << "The value v was not found in the array!" << endl;
	}
	}
	else //else if input invalid
	{
		cout << "ERROR: you entered an incorrect value for the array size!" << endl;
	}
	return 0;
}
