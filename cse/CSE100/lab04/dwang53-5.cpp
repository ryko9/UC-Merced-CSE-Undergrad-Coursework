//David Wang, CSE100, Lab04

#include <iostream>
#include <climits>
using namespace std;

int maxCross(int A[], int low, int mid, int high)
{
	int leftSum = INT_MIN;
	int rightSum = INT_MIN;
	int leftMax;
	int rightMax;

	int sum = 0;

	for(int i = mid + 1; i <= high; i++)
	{
		sum += A[i];

		if(sum > rightSum)
		{
			rightSum = sum;
			rightMax = i; 
		}
	}

	sum = 0;

	for(int i = mid; i >= low; i--)
	{
		sum+= A[i];

		if(sum > leftSum)
		{
			leftSum = sum;
			leftMax = i;
		}
	}

	return(leftSum + rightSum);
}

int maxSub(int A[], int low, int high)
{

	if(high == low)
	{
		return A[low];
	}
	else 
	{
		int mid = (low + high)/2;
		int leftSum = maxSub(A, low, mid);
		int rightSum = maxSub(A, mid + 1, high);
		int crossSum = maxCross(A, low, mid, high);

		if((leftSum >= rightSum) && (leftSum >= crossSum))
		{
			return leftSum;
		}
		else if((rightSum >= leftSum) && (rightSum >= crossSum))
		{
			return rightSum;
		}
		else
		{
			return crossSum;
		}
	}

}

int main()
{
	int n; //stores size of array
	cin >> n;

	int A[n]; //array A with size N declared

	for(int i = 0; i < n; i++) //input values for array elements
	{
		cin >> A[i];
	}

	cout << maxSub(A, 0, n - 1);

}