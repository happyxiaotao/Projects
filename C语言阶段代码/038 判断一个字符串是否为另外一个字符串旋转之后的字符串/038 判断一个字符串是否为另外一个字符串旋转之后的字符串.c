/*
Copyrights (c) 2016, ���ƴ�8555��ʯ����
All rights resverse

�ļ����ƣ�
�ļ���ʶ��
ժ    Ҫ���ж�һ���ַ����Ƿ�Ϊ����һ���ַ�����ת֮����ַ�����
		  ���磺����s1 �� AABCD��s2 = BCDAA������1������s1=abcd��s2=ACBD������0.
			AABCD����һ���ַ��õ�ABCDA
			AABCD���������ַ��õ�BCDAA

			AABCD����һ���ַ��õ�DAABC
			AABCD���������ַ��õ�CDAAB


��ǰ�汾��
��    �ߣ�ʯ����
������ڣ�2016/11/12
*/
//ʵ��ģ��strcmp, strcpy, strlen, strstr,



/*
���п��ܣ�
1,dest, src Ϊ��
2������""�ַ���
3��dest��src��С��ͬ
*/
#include <stdio.h>
#include <string.h>
#include <assert.h>
int Is_rotate(const char *dest, const char *src)
{

	int len_1 = strlen(dest);
	int len_2 = strlen(src);

	char *s1 = (char *)dest;
	char *s2 = (char *)src;
	
	assert(dest != NULL);
	assert(src != NULL);
	
	if (len_1 != len_2)
	{
		return 0;
	}

	if (0 == len_1)
	{
		return 1;
	}

	while (*s2)
	{
		if (*s1 == *s2)
		{
			break;
		}

		s2++;
	}

	if (*s2 == '\0')
	{
		return 0;
	}

	while (*s1)
	{
		if ('\0' == *s2)
		{
			s2 = (char *)src;
		}

		if (*s1 != *s2)
		{
			return 0;
		}

		s1++;
		s2++;
	}

	return 1;
}

int main()
{
	char dest[] = "ABCD";
	char src1[] = "BCDA";
	char src2[] = "ACBD";

	int ret1 = Is_rotate(dest, src1);
	int ret2 = Is_rotate(dest, src2);

	printf("ret1 = %d\n", ret1);
	printf("ret2 = %d\n", ret2);

	return 0;
}