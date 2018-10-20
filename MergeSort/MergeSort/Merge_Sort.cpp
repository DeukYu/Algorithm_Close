#include <iostream>
#include <time.h>
#include <random>

#define SIZE 10

int iTemp[SIZE] = {};

using namespace std;

void merge(int list[], int left, int middle, int right) // �պ�
{
	int l = left;
	int r = middle + 1;
	int iCount = left;

	// ���� ���ĵ� list�� �պ�
	while (l <= middle && r <= right)
	{
		if (list[l] <= list[r])
			iTemp[iCount++] = list[l++];
		else
			iTemp[iCount++] = list[r++];
	}
	
	// ���� �ִ� ������ �ϰ� ����
	if (l > middle)
	{
		while (r <= right)
			iTemp[iCount++] = list[r++];
	}
	else
	{
		while (l <= middle)
			iTemp[iCount++] = list[l++];
	}
	for (int i = left; i <= right; ++i)
		list[i] = iTemp[i];
}

void sortMerge(int list[], int left, int right)
{
	int middle{};
	if (left < right)
	{
		middle = (left + right) / 2; // �߰� ��ġ

		sortMerge(list, left, middle);
		sortMerge(list, middle + 1, right);

		merge(list, left, middle, right);
	}
}

int main()
{
	srand((unsigned int)time(0));

	int data[SIZE] = {};

	for (int i = 0; i < SIZE; ++i)
	{
		data[i] = rand() % 1000;
	}

	cout << "���� ��" << endl;
	for (int i = 0; i < SIZE; ++i)
	{
		cout << data[i] << " ";
	}
	cout << endl;

	sortMerge(data, 0, SIZE - 1);
	cout << "���� ��" << endl;
	for (int i = 0; i < SIZE; i++) {
		cout << data[i] << " ";
	}
	cout << endl;
	return 0;
}