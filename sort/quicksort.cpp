#include <iostream>
#include <algorithm>
#include <tuple>
using namespace std;


int part2(int arr[], int i, int j)
{
	int val = arr[j];
	int cur = i;
	for (int low = i; low < j; ++low)
	{
		if (arr[low] < val)
		{
			swap(arr[low], arr[cur]);
			++cur;
		}
	}
	swap(arr[cur], arr[j]);
	return cur;
}

int part(int arr[], int i, int j)
{
	int val = arr[i];
	
	while (i < j)
	{
		while (i < j && arr[j] >= val)
			--j;
		arr[i] = arr[j];
		while (i < j && arr[i] <= val)
			++i;
		arr[j] = arr[i];
	}

	arr[i] = val;
	return i;
}

void quickSort(int arr[], int i, int j)
{
	if (i >= j)
		return;

	int mid = part2(arr, i, j);
	quickSort(arr, i, mid - 1);
	quickSort(arr, mid + 1, j);
}

int main()
{
	int arr[] = { 10, 11, 12, 9, 9, 20 };

	quickSort(arr, 0, sizeof(arr) / sizeof(arr[0]) - 1);
	
	for_each(arr, arr + sizeof(arr) / sizeof(arr[0]), [](int e){ cout << e << endl; } );

	return 0;
}