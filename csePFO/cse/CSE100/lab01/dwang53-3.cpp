/* David Wang CSE100 */

#include <iostream>
using namespace std;

int linearSearch(int A[], int length, int key) //(array pointer, length of array, and key to find)
{
	for(int i = 0; i < length; i++)
	{
		if(A[i] == key)
		{
			return i;
		}
	}

	return -1; //if nothing is returned, goes to default -1 for no matches.
}

int main()
{
	int n; //number of elements for array
	cin >> n; //input num of elements
	int arr[n]; //declare array with n elements

	int x; 
	cin >> x; //input value to find

	for(int i = 0; i < n; i++)
	{
		cin >> arr[i]; //loop to input each value at a time.
	}

	cout << linearSearch(arr, n, x) << endl; //call search function, and output the result.

}