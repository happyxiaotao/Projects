/*
����һ��double���͵ĸ�����base��int���͵�����exponent����base��exponent�η���
*/
#include <stdio.h>
#include <math.h>
#define ESPINON 1E-16
double Power(double base, int exponent) 
{
	if ((1E-16 >= base) && (-1E-16 <= base))
		return 0;

	if (0 == exponent)
		return 1;
	
	double sum = 1;
	bool flag = true;

	if (0 > exponent)
	{
		exponent *= -1;
		flag = false;
	}

	while (exponent--)
		sum *= base;

	return flag?sum:1/sum;
}

int main()
{
	return 0;
}