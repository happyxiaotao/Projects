#include <stdio.h>

int getGcd(int value1, int value2)
{
	int gcd = 0;
	int divisor = 0;
	
	do
	{
		divisor = value1 % value2;

		gcd = value2;

		value1 = value2;
		value2 = divisor;

	}while(divisor);

	return gcd;
}

int main()
{
	int value1 = 0;
	int value2 = 0;
	int gcd = 0;
	int choice = 1;

	while(choice)
	{
		printf("输入value1，和value2：");
		scanf("%d%d",&value1,&value2);
		gcd = getGcd(value1, value2);
		printf("gcd = %d\n",gcd);

		printf("1——继续，0——退出\n");
		scanf("%d",&choice);
	}



	return 0;
}