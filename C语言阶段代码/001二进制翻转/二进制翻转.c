#include <stdio.h>

unsigned int  reverse_bit(unsigned int value);
int main()
{
	int value = 0;

	printf("输入正数：");
	scanf("%d",&value);
	//假设32位
	printf("二进制翻转后值为：%u\n",reverse_bit(value));

	return 0;
}
unsigned int reverse_bit(unsigned int value)
{
	int ret = 0;
	int i = 0;

	for(i = 0; i < 32; i++)
	{
		int tmp = 0;

		tmp = value & 1;

		ret <<= 1;

		ret |= tmp;

		value >>= 1;
	}

	return ret;
}