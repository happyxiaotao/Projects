/*
Copyrights (c) 2016, 西科大8555室石俊涛
All rights resverse

文件名称：
文件标识：
摘    要：实现可变参数函数:Max ,求最大值

当前版本：
作    者：石俊涛
完成日期：2016/11/06
*/
#include <stdio.h>
#include <stdarg.h>

int Max(int n,...)
{
	int i = 0;
	int max = 0;

	va_list arg;
	va_start(arg,n);

	max = va_arg(arg, int);

	for (i = 1; i < n; i++)
	{
		int tmp = va_arg(arg, int);

		if (max < tmp)
		{
			max = tmp;
		}
	}

	va_end(arg);

	return (max);
}

int main()
{
	int max = Max(6,6,4,4,2,7,100);

	printf("max = %d\n", max);

	return 0;
}