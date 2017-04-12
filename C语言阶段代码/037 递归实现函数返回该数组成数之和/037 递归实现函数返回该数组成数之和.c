#include <stdio.h>

int DigitSum(int n)
{
	if (n)
	{
		int digit = n % 10;
		return (digit+DigitSum(n/10));
	}
	else
	{
		return 0;
	}
}

int main()
{
	int n = 1729;

	int ret = DigitSum(n);

	printf("ret = %d\n", ret);

	return 0;
}