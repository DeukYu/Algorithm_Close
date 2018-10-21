#include <iostream>

using namespace std;

void hanoi_tower(int n, char from, char temp, char to)
{
	if (n == 1)
		cout << "원판 1을 " << from << "에서 " << to << "로 옮긴다." << endl;
	else
	{
		hanoi_tower(n - 1, from, to, temp);
		cout << "원판 " << n << "을 " << from << "에서 " << to << "로 옮긴다." << endl;
		hanoi_tower(n - 1, temp, from, to);
	}
}

int main()
{
	hanoi_tower(4, 'a', 'b', 'c');
}