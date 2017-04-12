/*
Copyrigh (c) 2016,西科大8555室石俊涛
All rights reserved

文件名称：用宏将数字的奇数位和偶数位交换.c
文件标识：暂无
再	  要：写一个宏可以将一个数字的奇数位和偶数位交换

当前版本：1.0
作	  者：石俊涛
完成日期：2016年10月31日
*/
//TDD

#include <stdio.h>
#include <math.h>

#define EXCHANGE_ODD_AND_EVEN_BIT(x) \
	{\
		int count = 0;\
		while(1)\
		{\
			int i = x/pow(10, count);\
			int j = x/pow(10, count+1);\
			if(j)\
			{\
				i %= 10;\
				j %= 10;\
				x -= i*pow(10, count);\
				x -= j*pow(10, count+1);\
				x += i*pow(10, count+1);\
				x += j*pow(10, count);\
			}\
			else\
				break;\
			count += 2;\
		}\
}



int ex(int *x)
{
	int count = 0;

	while(1)
	{
		int i = *x/pow(10, count);
		int j = *x/pow(10, count+1);

		if(j)
		{	
			i %= 10;
			j %= 10;

			*x -= i*pow(10, count);
			*x -= j*pow(10, count+1);

			*x += i*pow(10, count+1);
			*x += j*pow(10, count);
		}
		else
			break;

		count += 2;

	}

	return *x;
}

int main()
{
	int var = 0;

	while (1)
	{
		printf("输  入: var > ");
		
		scanf("%d",	&var);

		//函数实现
		//printf("交换后：var = %d\n", ex(&var));
		//用宏实现
		EXCHANGE_ODD_AND_EVEN_BIT(var);
		printf("交换后：var = %d\n", var);
	}

	return 0;
}