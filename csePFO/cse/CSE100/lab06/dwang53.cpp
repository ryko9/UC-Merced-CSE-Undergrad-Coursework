/* David Wang, CSE100, Lab 06 */

#include <iostream>
#include <math.h>
using namespace std;

int part(int A[], int p, int r) //function to partition
{
	int x = A[r];
	int i = p - 1;

	for(int j = p; j <= r - 1; j++)
	{
		if(A[j] <= x)
		{
			i++;
			swap(A[i], A[j]);
		}
	}
	swap(A[i+1], A[r]);
	return (i + 1);
}

int randomPart(int A[], int p, int r) //randomized version of partition
{

	int i = rand() % (r - p) + p;
	swap(A[r], A[i]);
	return part(A, p, r);
}

void quickSort(int A[], int p, int r)
{
	if(p < r)
	{
		int q = randomPart(A, p, r);
		quickSort(A, p, q - 1);
		quickSort(A, q + 1, r);
	}
}

int main()
{
	int n; //size of array
	cin >> n;

	int A[n]; //declare array size n

	int count = 0;
	while(count != n)
	{
		cin >> A[count];
		count++;
	}

	quickSort(A, 0, n - 1);
	for(int i = 0; i < n; i++)
	{
		cout << A[i] << ";";
	}

	return 0;
}
