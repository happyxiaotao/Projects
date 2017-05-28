#include <stdio.h>
#include <math.h>

int Is_prime(int n);

int main()
{
	int num = 0;

	printf("����һ������");
	scanf("%d",&num);

	if(Is_prime(num))
		printf("%d������\n",num);
	else
		printf("%d��������\n",num);

	return 0;
}

//������prime number���ֳ������������޸���
//��������Ϊ�ڴ���1����Ȼ���У�����1�����������ⲻ������������������Ϊ������
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