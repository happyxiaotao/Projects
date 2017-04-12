/*
Copyrights (c) 2016, 西科大8555室石俊涛
All rights resverse

文件名称：
文件标识：
摘    要：实现可变参数函数：average，求平均值

当前版本：
作    者：石俊涛
完成日期：2016/11/06
*/
/*
va_list arg;
va_start(arg, n);
va_arg(arg, int);
va_end(arg);
*/
#include <stdio.h>
#include <stdarg.h>

int average(int n,...)
{	
	int i = 0;
	int sum = 0;
	va_list arg;
	va_start(arg, n);

	for (i = 0; i < n; i++)
	{
		sum += va_arg(arg, int);
	}

	va_end(arg);

	return (sum/n);
}

int main()
{
	int ret = average(6,1,2,3,5,6,7);
	
	printf("平均值是：%d\n", ret);

	return 0;
}