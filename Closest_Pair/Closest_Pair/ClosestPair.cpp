#include <iostream>
#include <random>
#include <time.h>

using namespace std;

struct tPos
{
	float x{}, y{};
};

void QuickSort(tPos* data, int left, int right)
{
	int L = left;
	int R = right;
	tPos temp;
	tPos pivot = data[(left + right) / 2];

	while (L <= R)
	{
		while (data[L].x < pivot.x)
			++L;
		while (data[R].x > pivot.x)
			--R;
		if (L <= R)
		{
			if (L != R)
			{
				temp = data[L];
				data[L] = data[R];
				data[R] = temp;
			}
			++L;
			--R;
		}
	}
	if (left < R)
		QuickSort(data, left, R);
	if (L < right)
		QuickSort(data, L, right);
}

float dist(tPos a, tPos b) // �� ���� �Ÿ��� ���ϴ� �Լ�
{
	return sqrtf((a.x - b.x) * (a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}

float min_comp(float a, float b) // �� ���� float ���� ��ȯ�ϴ� �Լ�
{
	return (a < b) ? a : b;
}

float cloest_pair(tPos* data, int size)
{
	// ���� ����
	int mid = size / 2;
	tPos mid_point = data[mid];

	if (size == 3) // ���� ������ 3���� ���, �� ���� �Ÿ��� ����.
	{
		float min = FLT_MAX;

		for (int i = 0; i < size; ++i)
		{
			for (int j = i + 1; j < size; ++j)
			{
				min = dist(data[i], data[j]);
				cout << "{" << data[i].x << ", " << data[i].y << "},\t"
					<< "{" << data[j].x << ", " << data[j].y << "} =>\t" << min << endl;
			}
		}
		return min;
	}
	else if (size == 2) // ���� ������ 2���� ���, �� ���� �Ÿ��� ����.
	{
		cout << "{" << data[0].x << ", " << data[0].y << "},\t"
			<< "{" << data[1].x << ", " << data[1].y << "} =>\t" << dist(data[0], data[1]) << endl;
		return dist(data[0], data[1]);
	}
	else // ���� ���� 4�� �̻��� ���, ���ʰ� ���������� ������.
	{
		float cp_left;
		float cp_right;
		if (size % 2 == 1)
		{
			cp_left = cloest_pair(data, mid + 1); // ����
			cp_right = cloest_pair(data + (mid + 1), size - (mid + 1)); // ������
		}
		else
		{
			cp_left = cloest_pair(data, mid); // ����
			cp_right = cloest_pair(data + mid, size - mid); // ������
		}

		float d = min_comp(cp_left, cp_right); // ���� ������ �Ÿ� ���Ͽ� �� ���� ���� d�� �ִ´�.

		// �ֱ������� ��
		tPos* cpc = new tPos[size];
		int num = 0;
		for (int i = 0; i < size; ++i)
		{
			if (abs(data[i].x - mid_point.x) < d)
			{
				cpc[num] = data[i];
				++num;
			}
		}
		for (int i = 1; i < num; ++i)
		{
			for (int j = i + 1; j < num; ++j)
			{
				if (dist(cpc[i], cpc[j]) < d)
				{
					d = dist(cpc[i], cpc[j]);
					cout << "{" << cpc[i].x << ", " << cpc[i].y << "},\t"
						<< "{" << cpc[j].x << ", " << cpc[j].y << "} =>\t" << dist(cpc[i], cpc[j]) << " (�߰�����)" << endl;
				}
			}
		}
		return d;
	}
}

int main()
{
	random_device rd;
	default_random_engine dre(rd());
	uniform_int_distribution<> uid(0, 1000);

	const int SIZE = 30;

	int point_mid = SIZE / 2;

	tPos tpoint[SIZE] = {};

	for (tPos& d : tpoint)
	{
		d.x = (float)uid(dre);
		d.y = (float)uid(dre);
	}

	cout << "{ ";
	for (tPos d : tpoint)
	{
		cout << "{" << d.x << ", " << d.y << "}, ";
	}
	cout << "}" << endl;

	QuickSort(tpoint, 0, SIZE - 1);

	cout << endl;

	cout << "�ִ� �Ÿ�: " << cloest_pair(tpoint, SIZE) << endl;
}