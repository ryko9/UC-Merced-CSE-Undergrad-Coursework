/* David Wang, Lab 00, CSE100 */

#include <iostream>
using namespace std;

void insertSort(int arr[], int 	n) //function to sort array, given an array and number of elements
{

	int i, key, j;

	for(int i = 1; i < n; i++) //starting from 1, index 0 becomes the first element of the sorted array
	{
		key = arr[i]; //stores unsorted array first value, starting from element 1 in this case. Element 0 becomes the first element of the sorted array.
		j = i - 1; //points to current sorted array value.

		while(j >= 0 && arr[j] < key) //checks if arr[j] > arr[i]. 
		{
			arr[j + 1] = arr[j]; //switches arr[i] with arr[j]
			j = j - 1; //As j increases, number of items in sorted array increases. The j - 1 and j >= 0 ensure that the arr[j] < key comparison goes from the current j to the first j element
		}

		arr[j + 1] = key; //after the while loop, all are sorted in the sorted array, so the key value is restored
	}

}

int main()
{

	int n; // number of elements in array to be sorted

	//inputting values

	cin >> n; //enter value for n

	int arr[n]; //declare array with n # of elements

	for (int i = 0; i < n; i++) //for loop to enter elements for array from arr[0] to arr[n]
	{
		cin >> arr[i]; 
	}

	insertSort(arr, n); //call insertSort function to sort array using insertion sort algorithm

	//outputting values

	for(int i = 0; i < n; i++)
	{
		cout << arr[i] << ";";
	}
}


