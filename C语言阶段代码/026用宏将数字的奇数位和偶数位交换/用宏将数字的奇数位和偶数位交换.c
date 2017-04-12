/*
Copyrigh (c) 2016,���ƴ�8555��ʯ����
All rights reserved

�ļ����ƣ��ú꽫���ֵ�����λ��ż��λ����.c
�ļ���ʶ������
��	  Ҫ��дһ������Խ�һ�����ֵ�����λ��ż��λ����

��ǰ�汾��1.0
��	  �ߣ�ʯ����
������ڣ�2016��10��31��
*/
//TDD

#include <stdio.h>
#include <math.h>

#define EXCHANGE_ODD_AND_EVEN_BIT(x) \
	{\
		int count = 0;\
		while(1)\
		{\
			int i = x/pow(10, count);\
			int j = x/pow(10, count+1);\
			if(j)\
			{\
				i %= 10;\
				j %= 10;\
				x -= i*pow(10, count);\
				x -= j*pow(10, count+1);\
				x += i*pow(10, count+1);\
				x += j*pow(10, count);\
			}\
			else\
				break;\
			count += 2;\
		}\
}



int ex(int *x)
{
	int count = 0;

	while(1)
	{
		int i = *x/pow(10, count);
		int j = *x/pow(10, count+1);

		if(j)
		{	
			i %= 10;
			j %= 10;

			*x -= i*pow(10, count);
			*x -= j*pow(10, count+1);

			*x += i*pow(10, count+1);
			*x += j*pow(10, count);
		}
		else
			break;

		count += 2;

	}

	return *x;
}

int main()
{
	int var = 0;

	while (1)
	{
		printf("��  ��: var > ");
		
		scanf("%d",	&var);

		//����ʵ��
		//printf("������var = %d\n", ex(&var));
		//�ú�ʵ��
		EXCHANGE_ODD_AND_EVEN_BIT(var);
		printf("������var = %d\n", var);
	}

	return 0;
}