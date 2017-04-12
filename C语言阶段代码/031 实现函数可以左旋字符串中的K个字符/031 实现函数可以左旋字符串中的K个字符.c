/*
Copyrights (c) 2016, 西科大8555室观赏
All rights reverse

文件名称：031 实现函数可以左旋字符串中的K个字符.c
文件标识：
摘    要：实现一个函数，可以左旋字符串中的k个字符

当前版本：
作者：观赏
完成日期：2016/11/04
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