/*
Copyrights (c) 2016, 西科大8555室石俊涛
All rights resverse

文件名称：
文件标识：
摘    要：求斐波那契数列第n项

当前版本：
作    者：石俊涛
完成日期：2016/11/06
*/

#include <stdio.h>
/*递归调用，效率太低
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
/*迭代*/
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
