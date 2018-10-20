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

float dist(tPos a, tPos b) // 두 점의 거리를 구하는 함수
{
	return sqrtf((a.x - b.x) * (a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}

float min_comp(float a, float b) // 더 작은 float 값을 반환하는 함수
{
	return (a < b) ? a : b;
}

float cloest_pair(tPos* data, int size)
{
	// 변수 선언
	int mid = size / 2;
	tPos mid_point = data[mid];

	if (size == 3) // 점의 개수가 3개일 경우, 세 점의 거리를 구함.
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
	else if (size == 2) // 점의 개수가 2개일 경우, 두 점의 거리를 구함.
	{
		cout << "{" << data[0].x << ", " << data[0].y << "},\t"
			<< "{" << data[1].x << ", " << data[1].y << "} =>\t" << dist(data[0], data[1]) << endl;
		return dist(data[0], data[1]);
	}
	else // 만약 점이 4개 이상일 경우, 왼쪽과 오른쪽으로 나눈다.
	{
		float cp_left;
		float cp_right;
		if (size % 2 == 1)
		{
			cp_left = cloest_pair(data, mid + 1); // 왼쪽
			cp_right = cloest_pair(data + (mid + 1), size - (mid + 1)); // 오른쪽
		}
		else
		{
			cp_left = cloest_pair(data, mid); // 왼쪽
			cp_right = cloest_pair(data + mid, size - mid); // 오른쪽
		}

		float d = min_comp(cp_left, cp_right); // 왼쪽 오른쪽 거리 비교하여 더 작은 값을 d에 넣는다.

		// 최근접점의 쌍
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
						<< "{" << cpc[j].x << ", " << cpc[j].y << "} =>\t" << dist(cpc[i], cpc[j]) << " (중간영역)" << endl;
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

	cout << "최단 거리: " << cloest_pair(tpoint, SIZE) << endl;
}