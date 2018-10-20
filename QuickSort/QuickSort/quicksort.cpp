#include <iostream>
#include <random>

using namespace std;

void swap(int& a, int& b)
{
	int iTemp = a;
	a = b;
	b = iTemp;
}

int partition(int* list, int left, int right)
{
	int r = list[right];
	int i{}, j{};

	while (true)
	{
		if (list[j] > r)
			++j;
		else if (list[j] < r)
		{
			swap(list[i], list[j]);
			++i;
			++j;
		}
		else if (j == right)
		{
			swap(list[i], list[j]);
			break;
		}
	}
	return i;
}

void QuickSort(int* list, int left, int right)
{
	int pivot{};
	if (left < right)
	{
		pivot = partition(list,left, right);
		QuickSort(list, left, pivot - 1);
		QuickSort(list, pivot + 1, right);
	}
}

int main()
{
	const int Size = 15;
	int Array[Size];
	random_device rd;
	default_random_engine dre(rd());
	uniform_int_distribution<> uid(0, 500);

	for (int& d : Array)
		d = uid(rd);

	cout << "Quick_Sort before" << endl;
	for (int d : Array)
		cout << d << ' ';
	cout << endl;

	QuickSort(Array, 0, Size - 1);

	cout << "Quick_Sort after" << endl;
	for (int d : Array)
		cout << d << ' ';
	cout << endl;
}