#include <stdio.h>
#include <math.h>

int Is_prime(int n);

int main()
{
	int num = 0;

	printf("输入一个数：");
	scanf("%d",&num);

	if(Is_prime(num))
		printf("%d是素数\n",num);
	else
		printf("%d不是素数\n",num);

	return 0;
}
int Is_prime(int n)
{
	int j = 0;

	for(j = 2; j <= sqrt(n); j++)
	{
		if(n%j == 0)
			return 0;
	}
	return 1;
}