/*
��飺쳲��������У�Fibonacci sequence�����ֳƻƽ�ָ����С�����ѧ���а��ɶࡤ쳲�������Leonardoda Fibonacci��
�����ӷ�ֳΪ���Ӷ����룬���ֳ�Ϊ���������С���ָ��������һ�����У�1��1��2��3��5��8��13��21��34������
����ѧ�ϣ�쳲��������������±��Եݹ�ķ������壺F(0)=1��F(1)=1, F(n)=F(n-1)+F(n-2)��n>=2��n��N*��

���⣺��Ҷ�֪��쳲��������У�����Ҫ������һ������n���������쳲��������еĵ�n�n<=39
*/
#include <stdio.h>
int Fibonacci(int n)
{
	int f0 = 0;
	int f1 = 1;
	int sum = 0;
	int i = 0;
	if (0 >= n)
		return 0;
	if (1 == n)
		return 1;
	/*
	for (; i < n-1; i++)
	{
		sum = f0 + f1;
		f0 = f1;
		f1 = sum;
	}
	*/
	while (--n)
	{
		sum = f0 + f1;
		f0 = f1;
		f1 = sum;
	}

	return sum;
}

int mian()
{
	return 0;
}