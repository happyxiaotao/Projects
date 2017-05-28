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

//质数（prime number）又称素数，有无限个。
//质数定义为在大于1的自然数中，除了1和它本身以外不再有其他因数的数称为质数。
int Is_prime(int n)
{
	int i = 0;
	
	if (n <= 1)
		return 0;
	
	if ((2 == n) || (3 == n))
		return 1;
	
	for(i = 2; i <= sqrt(n); ++i)
	{
		if(n%i == 0)
			return 0;
	}
	return 1;
}