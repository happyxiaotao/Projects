#include <stdio.h>

int Pow(int x, unsigned int n)
{
	if (0 == n)
		return 1;

	if (n&1)//ÆæÊý
		return Pow(x, n-1)*x;
	else
		return Pow(x*x, n>>1);
}

int main()
{
	
	int i = 0;
	for (; i <= 10; ++i)
		printf("2^%d = %d\n", i, Pow(2,i));

	return 0;
}