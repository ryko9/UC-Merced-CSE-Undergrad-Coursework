/* David Wang
   CSE 100
   Lab05 HeapSort
*/

#include <iostream>
using namespace std;

int Right(int n)
{
	return 2 * n + 2;
}

int Left(int n)
{
	return 2 * n + 1;
}

int Parent(int n)
{
	return n/2;
}


int maxHeap(int A[], int size, int n)
{
	int max;
	int left = Left(n);
	int right = Right(n);

	if((left < size) && (A[left] >= A[n]))
	{
		max = left;
	}
	else
	{
		max = n;
	}

	if((right < size) && (A[right] >= A[max]))
	{
		max = right;
	}
	if (max != n)
	{
		swap(A[n], A[max]);
		maxHeap(A , size, max);
	}

}

void buildMax(int A[], int size)
{ 
	size = size - 1; 
	for(int n = Parent(size) - 1; n >= 0; n--)
	{
		maxHeap(A, size, n);
	}
}

void heapSort(int A[], int size)
{
	 buildMax(A, size);

	 for(int n = size - 1; n >= 0; n--)
	 {
	 	swap(A[0], A[n]);
	 	maxHeap(A, n, 0);
	 }
}

int main()
{
	int size;
	cin >> size;

	int A[size];
	int n;

	for(n = 0; n < size; n++)
	{
		cin >> A[n];
	}

	heapSort(A, size);

	for(n = 0; n < size; n++)
	{
		cout << A[n] << ";";
	}

	return 0;
}