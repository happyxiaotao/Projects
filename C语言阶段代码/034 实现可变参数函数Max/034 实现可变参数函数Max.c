/*
Copyrights (c) 2016, ���ƴ�8555��ʯ����
All rights resverse

�ļ����ƣ�
�ļ���ʶ��
ժ    Ҫ��ʵ�ֿɱ��������:Max ,�����ֵ

��ǰ�汾��
��    �ߣ�ʯ����
������ڣ�2016/11/06
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