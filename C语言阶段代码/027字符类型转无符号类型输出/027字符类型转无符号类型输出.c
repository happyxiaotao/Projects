/*
Copyrights (c) 2016�����ƴ�8555��ʯ����
All rights resverse

�ļ����ƣ�
�ļ���ʶ��
ժ    Ҫ��

��ǰ�汾��
��    �ߣ�
������ڣ�2016/11/01
*/
#include <stdio.h>

int main()
{	
	const char n = -1;
	const char i = -128;
	const char j = 128;

	printf("n = %u\n", n);
	printf("i = %u\n", i);
	printf("j = %u\n", j);

	printf("(n - i)��ֵΪ��%d\n", n - i);

	printf("(n - i)��ֵΪ��%u\n", n - i);

	printf("(n - i)��ֵΪ��%u\n", (unsigned int)n - (unsigned int)i);

	printf("(n - j)��ֵΪ��%d\n", n - j);

	printf("(n - j)��ֵΪ��%u\n", n - j);

	printf("(n - j)��ֵΪ��%u\n", (unsigned int)n - (unsigned int)j);

	printf("(n - j)��ֵΪ��%u\n", (unsigned int)i - (unsigned int)j);

	return 0;
}