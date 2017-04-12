/*
Copyrights (c) 2016, ���ƴ�8555��ʯ����
All rights resverse

�ļ����ƣ�
�ļ���ʶ��
ժ    Ҫ��ʵ�ֿɱ����������average����ƽ��ֵ

��ǰ�汾��
��    �ߣ�ʯ����
������ڣ�2016/11/06
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
	
	printf("ƽ��ֵ�ǣ�%d\n", ret);

	return 0;
}