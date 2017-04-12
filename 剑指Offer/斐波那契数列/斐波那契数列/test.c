/*
简介：斐波那契数列（Fibonacci sequence），又称黄金分割数列、因数学家列昂纳多·斐波那契（Leonardoda Fibonacci）
以兔子繁殖为例子而引入，故又称为“兔子数列”，指的是这样一个数列：1、1、2、3、5、8、13、21、34、……
在数学上，斐波纳契数列以如下被以递归的方法定义：F(0)=1，F(1)=1, F(n)=F(n-1)+F(n-2)（n>=2，n∈N*）

问题：大家都知道斐波那契数列，现在要求输入一个整数n，请你输出斐波那契数列的第n项。n<=39
*/
#include <stdio.h>
int Fibonacci(int n)
{
	int f0 = 0;
	int f1 = 1;
	int sum = 0;
	int i = 0;
	if (0 >= n)
		return 0;
	if (1 == n)
		return 1;
	/*
	for (; i < n-1; i++)
	{
		sum = f0 + f1;
		f0 = f1;
		f1 = sum;
	}
	*/
	while (--n)
	{
		sum = f0 + f1;
		f0 = f1;
		f1 = sum;
	}

	return sum;
}

int mian()
{
	return 0;
}