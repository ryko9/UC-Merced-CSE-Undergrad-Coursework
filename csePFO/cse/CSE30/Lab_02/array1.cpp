#include <iostream>
using namespace std;

int main()
{
	int arrSize; //for storing size of array
	bool increasing = true; //for checking if array is increasing

	cout << "Enter the size of the array: ";
	cin >> arrSize;

	if(arrSize > 0) //if array size is valid, proceed
	{
		int arr[arrSize];
		cout << "Enter the numbers in the array, seperated by a space, and press enter: ";

		for(int i = 0; i < arrSize; i++) //assigning elements
		{
			cin >> arr[i];
		}

		for (int i = 0; i < arrSize - 1; i++) //checking to see if array is increasing
		{
			if(arr[i] > arr[i + 1]) //if any consecutive elements are found to be
			//decreasing, then the whole array is not increasing. otherwise, if none
			//are found then increasing boolean will remain true.
			{
				increasing = false;
			}
		}

		if(increasing == true) //output based on whether or not increasing is true/false
		{
			cout << "This IS an increasing array!" << endl;
		}
		else
		{
			cout << "This is NOT an increasing array!" << endl;
		}

		for (int i = 0; i < arrSize; i++) //printing out array
		{
			cout << arr[i] <<  " ";

			if(i == arrSize - 1)
			{
				cout << endl; //if it reaches last number, endline for clarity
			}
		}

	}
	else	//if array size is invalid.
	{
		cout << "ERROR: You entered an incorrect value for the array size!" << endl;
	}

	return 0;
}
