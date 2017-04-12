/*
Copyrights (c) 2016, 西科大8555室石俊涛
All rights reverse

文件名称：029 编程求得20元能喝多少瓶汽水.c
文件标识：
摘	  要：每瓶汽水1元，两个空瓶可以置换一瓶汽水，
		  现有20元，最多能喝多少瓶汽水

当前版本：
作    者：石俊涛
完成日期：2016/11/04
*/

#include <stdio.h>

int drink_count(float cash, const float price)
{
	int empty_bottles = 0;
	int count = 0;
	while (cash >1E-10)
	{
		cash -= price;
		empty_bottles++;

		//if((empty_bottles & 1) == 0)
		if ((empty_bottles % 2) == 0)
		{
			empty_bottles++;
		}
	}

	return empty_bottles;
}

int main()
{
	float cash = 20.0;
	float price = 1.0;

	int count = 0;

	count = drink_count(cash, price);
	
	printf("count = %d\n", count);

	return 0;
}