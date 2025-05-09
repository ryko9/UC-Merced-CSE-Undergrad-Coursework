/* David Wang CSE100 */

#include <iostream>
using namespace std;

int binarySearch(int A[], int low, int high, int key) //Array pointer, low, high, and key
{
	while (low <= high)
	{
		int mid = (low + high)/2;

		if (A[mid] == key) //check if middle element is key
			return mid; 

		if (A[mid] > key) //if mid is greater than key, key must be in left portion
			return binarySearch(A, 0, mid - 1, key); // call again with high = mid - 1 to shift to left aportion
		return binarySearch(A, mid + 1, high, key); //if not the above conditionals, shift to right with low of mid + 1		
	}

	return -1; //if not present
}

int main()
{
	//initializing array
	int n; //num elements
	cin >> n;
	int arr[n];

	int key;
	cin >> key; //inputting key

	for(int i = 0; i < n; i++)
	{
		cin >> arr[i]; //inputting values of array
	}

	cout << binarySearch(arr, 0, n, key); //print out result of binarySearch call

	return 0;
}