/* David Wang CSE100 */

#include <iostream>
using namespace std;

void Merge(int a[], int low, int high, int mid)
{
	int i, j, k, tempArr[high - low + 1];

	i = low;
	k = 0;
	j = mid + 1;

	while(i <= mid && j <= high)
	{
		if (a[i] < a[j])
		{
			tempArr[k] = a[i];
			k++;
			i++;
		}
		else
		{
			tempArr[k] = a[j];
			{
				k++;
				j++;
			}
		}
	}

	while(i <= mid)
	{
		tempArr[k] = a[i];
		k++;
		i++;
	}

	while(j <= high)
	{
		tempArr[k] = a[j];
		k++;
		j++;
	}

	for(i = low; i <=high; i++)
	{
		a[i] = tempArr[i - low];
	}
}

void MergeSort(int a[], int low, int high)
{
	int mid;
	if(low < high)
	{
		mid = (low + high)/2;
		MergeSort(a, low, mid); //Sorts left half
		MergeSort(a, mid+1, high);// Sorts right half

		Merge(a, low, high, mid); //merges halves
	}
}

int main()
{
	int n; //init arr
	cin >> n;

	int arr[n];

	for(int i = 0; i < n; i++)
	{
		cin >> arr[i]; //inputting values
	}

	MergeSort(arr, 0, n - 1);

	for(int i = 0; i < n; i++)
	{
		cout << arr[i] << ";";
	}

	return 0;
}
