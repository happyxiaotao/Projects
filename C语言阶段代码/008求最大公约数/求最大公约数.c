#include <stdio.h>

#ifndef true
#define true 1
#endif //true

//�ǵݹ鷽ʽ 
int getGcd_Nor(int m, int n)
{
	int divisor = 0;//����ÿ��ѭ���е�����
	
	if ((0 == m) || (0 == n)) //0û��Լ��һ˵
		return 0;
		
	if (m < 0)/*��m��n��������ʱ��ֻ�轫����ȥ��������ֵ*/
		m = -m;
	if (n < 0)
		n = -n;
		
	if (m < n)//m < n,����������ֵ��m��Զ����ϴ�����ֵ
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

//�ݹ鷽ʽ��ֻ����m>n>0����������Ľ���
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
		printf("����value1����value2��");
		scanf("%d%d",&m,&n);
		if (gcd = getGcd_Nor(m, n))
			printf("gcd = %d\n",gcd);
		else
			printf("%d��%dû�й�Լ��\n", m, n);

//		printf("1����������0�����˳�\n");
//		scanf("%d",&choice);
	}

	return 0;
}