/*
Copyrights (c) 2016, ���ƴ�8555�ҹ���
All rights reverse

�ļ����ƣ�031 ʵ�ֺ������������ַ����е�K���ַ�.c
�ļ���ʶ��
ժ    Ҫ��ʵ��һ�����������������ַ����е�k���ַ�

��ǰ�汾��
���ߣ�����
������ڣ�2016/11/04
*/
#include <stdio.h>
#include <assert.h>

int m_strlen(const char *dest)
{
	int count = 0;
	assert(dest);

	while (*dest++)
	{
		count++;
	}
	return count;
}

char *left_move(char *dest, int k)
{
	char *ret = dest;
	int len = m_strlen(dest);

	assert(dest);

	k = k % len;

	while (k)
	{
		char tmp = dest[0];
		int i = 0;
		for (i = 0; i < len-1; i++)
		{
			dest[i] = dest[i+1];
		}
		dest[i++] = tmp;
		dest[i] = '\0';

		k--;
	}
	
	return ret;
}

int main()
{
	char str[] = "abcdef";
	int k = 0;

	printf("input k = ");
	scanf("%d", &k);

	left_move(str, k);

	printf("%s\n", str);

	return 0;
}