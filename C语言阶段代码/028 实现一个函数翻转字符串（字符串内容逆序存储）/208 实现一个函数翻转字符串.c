/*
Copyrights (c) 2016, ���ƴ�8555��ʯ����
All rights resverse

�ļ����ƣ�
�ļ���ʶ��
ժ    Ҫ��ʵ��һ��������ת�ַ�������һ���ַ��������ݣ�����洢��
			���磺���������ǣ�char arr[] = "abcdef";
			������������ݣ�"fedcba"

��ǰ�汾��
��    �ߣ�ʯ����
������ڣ�2016/11/04
*/

#include <stdio.h>
#include <assert.h>

int m_strlen(const char *dest)
{
	int len = 0;

	assert(dest);

	while (*dest++)
	{
		len++;
	}

	return len;
}

char *reverse(char *left, char *right) 
{
	char *ret = left;

	assert(left);
	assert(right);

	while (left < right)
	{
		char tmp = *left;
		*left = *right;
		*right = tmp;

		left++;
		right--;
	}

	return ret;
}

int main()
{
	char arr[] = "abcdef";
	
	int len = strlen(arr);

	reverse(arr, arr+len-1);

	printf("%s\n", arr);

	return 0;
}