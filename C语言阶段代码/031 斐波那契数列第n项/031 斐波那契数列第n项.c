/*
Copyrights (c) 2016, ���ƴ�8555��ʯ����
All rights resverse

�ļ����ƣ�
�ļ���ʶ��
ժ    Ҫ����쳲��������е�n��

��ǰ�汾��
��    �ߣ�ʯ����
������ڣ�2016/11/06
*/

#include <stdio.h>
/*�ݹ���ã�Ч��̫��
int fib(int n)
{
	if (n <= 2)
	{
		return 1;
	}
	else
	{
		return fib(n-1)+fib(n-2);
	}
}*/
/*����*/
int fib(int n)
{
	int a = 1;
	int b = 1;
	int c = 1;

	while (n>2)
	{
		c = a + b;
		a = b;
		b = c;

		n--;
	}

	return c;	
}
int main()
{
	int n = 5;
	int ret = fib(4);

	printf("ret = %d\n", ret);
}
