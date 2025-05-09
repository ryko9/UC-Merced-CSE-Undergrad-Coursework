#include <iostream>
using namespace std;

void sortArr(int isAscending, int arr[], int size)
{

	if(isAscending == 0) //ascending insertionsort
	{
		for(int i = 1; i < size; i++)
		{
			int max = arr[i];
			int j = i;

			while(j > 0 && arr[j - 1] > max) //while j is over 0 and any numbers before max are larger
			{
				arr[j] = arr[j - 1]; //the larger number that was bigger than a[j] is moved up
				j = j - 1; //the index of j decreases so next iteration of while loop will
				//compare the terms after the larger numbers that were moved up
			}

			arr[j] = max; //after all numbers have been sorted, places the number we designated as max
					//behind all the other numbers.
		}
	}

	if(isAscending == 1) //descending insertionsort
	{
		for(int i = 1; i < size; i++)
		{
			int min = arr[i];
			int j = i;

			while(j > 0 && arr[j - 1] < min) //now if i[j - 1] is SMALLER than i[j] it will be moved up
			{
				arr[j] = arr[j - 1];
				j = j - 1;
			}

			arr[j] = min;
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

