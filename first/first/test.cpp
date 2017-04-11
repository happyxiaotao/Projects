#include <iostream>
using namespace std;

int main()
{
	int *p = new int[10];

	for (int i = 0; i < 10; ++i)
		p[i] = i;
	int *p2 = p + 1;
	cout << "*p2 = " << *p2 << endl;

	delete p;

	system("pause");
	return 0;
}