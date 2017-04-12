/*
���ǿ�����2*1��С���κ��Ż�������ȥ���Ǹ���ľ��Ρ�
������n��2*1��С�������ص��ظ���һ��2*n�Ĵ���Σ��ܹ��ж����ַ�����
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