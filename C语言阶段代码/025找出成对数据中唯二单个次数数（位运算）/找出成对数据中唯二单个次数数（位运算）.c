
/*
Copyrights (c) 2016,西科大8555石俊涛
All rights resverse

文件名称：test.c
文件标识：000
摘    要：有一组数字，有两个数字只出现了一次，其他数字都是成对
		  出现的，请找出这个数字。

当前版本：1.0
作    着：石俊涛
完成日期：2016/10/31
*/
#include <stdio.h>

int main()
{
	int arr[] = {1, 1, 10, 2, 2, 5, 5, 8, 7, 7, 10, 10};
	int sz = sizeof(arr)/sizeof(int);
	int i = 0;
	int ret = 0;
	int bit_0 = 0;
	int bit_1 = 0;
	int count = 0;

	for (i = 0; i < sz; i++)
	{
		ret ^= arr[i];
	}

	while ((ret&1) != 1)
	{	
		count++;
 
		ret >>= 1;
	}
	
	for (i = 0; i < sz; i++)
	{
		if ((arr[i]>>count)&1)
		{
			bit_1 ^= arr[i];
		}
		else
		{
			bit_0 ^= arr[i];
		}
	}

	printf("其中两个奇数次的数：m = %d, n = %d\n", bit_0, bit_1);

	return 0;
}