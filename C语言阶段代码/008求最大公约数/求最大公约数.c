#include <stdio.h>

#ifndef true
#define true 1
#endif //true

//非递归方式 
int getGcd_Nor(int m, int n)
{
	int divisor = 0;//保存每次循环中的余数
	
	if ((0 == m) || (0 == n)) //0没有约数一说
		return 0;
		
	if (m < 0)/*当m或n存在正数时，只需将符号去掉，再求值*/
		m = -m;
	if (n < 0)
		n = -n;
		
	if (m < n)//m < n,交换两数的值，m永远保存较大数的值
	{
		int temp = m;
		m = n;
		n = temp;
	}

	divisor = m%n;
	while (divisor)
	{
		m = n;
		n = divisor;
		divisor = m%n;
	}

	return n;
}

//递归方式（只考虑m>n>0的情况，待改进）
int getGcd(int m, int n)
{
	if (0 == n)
		return m;
	return getGcd(n, m%n);
}

int main()
{
	int m = 0;
	int n = 0;
	int gcd = 0;
	int choice = 1;

	while(true/*choice*/)
	{
		printf("输入value1，和value2：");
		scanf("%d%d",&m,&n);
		if (gcd = getGcd_Nor(m, n))
			printf("gcd = %d\n",gcd);
		else
			printf("%d与%d没有公约数\n", m, n);

//		printf("1——继续，0——退出\n");
//		scanf("%d",&choice);
	}

	return 0;
}