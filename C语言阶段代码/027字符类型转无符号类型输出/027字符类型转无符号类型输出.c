/*
Copyrights (c) 2016，西科大8555室石俊涛
All rights resverse

文件名称：
文件标识：
摘    要：

当前版本：
作    者：
完成日期：2016/11/01
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

	printf("(n - i)差值为：%d\n", n - i);

	printf("(n - i)差值为：%u\n", n - i);

	printf("(n - i)差值为：%u\n", (unsigned int)n - (unsigned int)i);

	printf("(n - j)差值为：%d\n", n - j);

	printf("(n - j)差值为：%u\n", n - j);

	printf("(n - j)差值为：%u\n", (unsigned int)n - (unsigned int)j);

	printf("(n - j)差值为：%u\n", (unsigned int)i - (unsigned int)j);

	return 0;
}