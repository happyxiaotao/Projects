/*
我们可以用2*1的小矩形横着或者竖着去覆盖更大的矩形。
请问用n个2*1的小矩形无重叠地覆盖一个2*n的大矩形，总共有多少种方法？
*/
#include <stdio.h>

int RectCover(int number)
{
	int f1 = 1;
	int f2 = 2;
	int sum = 0;
	if (0 >= number)
		return 0;
	if ((1 == number) || (2 == number))
		return number;

	while (3 <= number--)
	{
		sum = f1 + f2;
		f1 = f2;
		f2 = sum;
	}
	return sum;
}
int main()
{
	int i = 0;
	for (; i < 10; i++)
		printf("i = %2d, sum = %d\n", i, RectCover(i));
	return 0;
}