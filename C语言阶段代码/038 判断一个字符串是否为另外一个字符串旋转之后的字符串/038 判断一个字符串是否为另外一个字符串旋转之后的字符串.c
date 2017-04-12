/*
Copyrights (c) 2016, 西科大8555室石俊涛
All rights resverse

文件名称：
文件标识：
摘    要：判断一个字符串是否为另外一个字符串旋转之后的字符串。
		  例如：给定s1 ＝ AABCD和s2 = BCDAA，返回1，给定s1=abcd和s2=ACBD，返回0.
			AABCD左旋一个字符得到ABCDA
			AABCD左旋两个字符得到BCDAA

			AABCD右旋一个字符得到DAABC
			AABCD右旋两个字符得到CDAAB


当前版本：
作    者：石俊涛
完成日期：2016/11/12
*/
//实现模拟strcmp, strcpy, strlen, strstr,



/*
所有可能：
1,dest, src 为空
2，传入""字符串
3，dest和src大小不同
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