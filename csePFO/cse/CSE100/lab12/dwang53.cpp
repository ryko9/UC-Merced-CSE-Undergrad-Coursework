//CSE 100 Lab 12
//David Wang 

#include <iostream>
#include <algorithm>
#include <climits>
using namespace std;

void bottomUpCut(int p[], int n)
{
	int q;
	int r[n];
	int s[n];
	r[0] = 0;

	for(int j = 1; j <= n; j++)
	{
		q = INT_MIN;
		for(int i = 1; i <= j; i++)
		{
			if(q < p[i - 1] + r[j - i])
			{
				q = p[i - 1] + r[j - i];
				s[j] = i;
			}
		}
		r[j] = q;
	}

//output 
	cout << r[n] << endl;

	while (n > 0)
	{
		cout << s[n] << " ";
		n = n - s[n];
	}

	cout << "-1" << endl;
}

int main()
{
	int size; 
	cin >> size;

	int A[size];

	for(int i = 0; i < size; i++)
	{
		cin >> A[i];
	}

	bottomUpCut(A, size);
	// printCutRod(A, size);
	// cout << "-1 ";
} 