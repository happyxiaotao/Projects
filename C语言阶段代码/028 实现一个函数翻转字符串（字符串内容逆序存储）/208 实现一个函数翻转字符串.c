/*
Copyrights (c) 2016, 西科大8555室石俊涛
All rights resverse

文件名称：
文件标识：
摘    要：实现一个函数翻转字符串（将一个字符串的内容，逆序存储）
			比如：数组内容是：char arr[] = "abcdef";
			逆序后：数组内容："fedcba"

当前版本：
作    者：石俊涛
完成日期：2016/11/04
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