/*
模拟实现pow函数
考虑点：
1，底数和指数都为分数时。
难点：
指数是分数时如何计算
*/
#include <stdio.h>

double m_pow(float n, int k)
{
	if (k > 0)
	{
		return (n * m_pow(n, k-1));
	}

	if (k == 0)
	{
		return 1;
	}

	if (k < 0)
	{
		return (1.0/n * m_pow(n, k+1));
	}
}

int main()
{
	float n = 0.5;
	int k = -3;

	double ret = m_pow(n, k);

	printf("ret = %lf\n", ret);

	return 0;
}
