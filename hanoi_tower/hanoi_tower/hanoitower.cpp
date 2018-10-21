#include <iostream>

using namespace std;

void hanoi_tower(int n, char from, char temp, char to)
{
	if (n == 1)
		cout << "���� 1�� " << from << "���� " << to << "�� �ű��." << endl;
	else
	{
		hanoi_tower(n - 1, from, to, temp);
		cout << "���� " << n << "�� " << from << "���� " << to << "�� �ű��." << endl;
		hanoi_tower(n - 1, temp, from, to);
	}
}

int main()
{
	hanoi_tower(4, 'a', 'b', 'c');
}