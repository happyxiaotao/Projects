/*
ÄÚÈİ£ºÎ²µİ¹é
*/
#include <iostream>
using namespace std;

int Fib(int first, int second, size_t N)
{
	if (N < 3)
		return 1;
	if (3 == N)
		return first+second;
	return Fib(second, first+second, N-1);
}

int main()
{
	int ret = Fib(1, 1, 5);
	cout << ret << endl;
	system("pause");
	return 0;
}