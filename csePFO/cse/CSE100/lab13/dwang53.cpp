/* David Wang, CSE 100, Lab 13 */
//used pseudocode from p.375 textbook.

#include <iostream>
#include <climits>
#include <vector>
using namespace std;

void printOptimal(vector < vector<int> > &s, int i, int j);

void printOptimal(vector< vector<int> >&s, int i, int j)
{
	if(i == j)
	{
		cout << "A" << i - 1;
	}
	else
	{
		cout << "(";
		printOptimal(s, i, s[i][j]);
		cout << ".";
		printOptimal(s, s[i][j] + 1, j);
		cout << ")";
	}
}

void matrixChain(int p[], int n)
{

	int m[n + 1][n + 1];

	vector <vector<int>> s;
	s.resize(n + 1, vector<int>(n + 1, 0));

	int z = 1;
	while (z != n + 1)
	{
		m[z][z] = 0;
		z++;
	}

	for (int l = 2; l <= n; l++)
	{
		for(int i = 1; i <= n - l + 1; i++)
		{
			int j = i + l - 1;
			m[i][j] = INT_MAX;

			for(int k = i; k <= j - 1; k++)
			{
				int q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
				if(q < m[i][j])
				{
					m[i][j] = q;
					s[i][j] = k;
				}
			}
		}
	}
	cout << m[1][n] << endl;
	printOptimal(s, 1, n);
	cout << endl;
}	

int main()
{
	int size;
	cin >> size;

	size++;
	int arr[size];

	int i = 0;
	while(i != size)
	{
		cin >> arr[i];
		i++;
	}

	size--;

	matrixChain(arr, size);
}