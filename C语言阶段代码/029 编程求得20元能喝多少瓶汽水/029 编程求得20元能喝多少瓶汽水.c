/*
Copyrights (c) 2016, ���ƴ�8555��ʯ����
All rights reverse

�ļ����ƣ�029 ������20Ԫ�ܺȶ���ƿ��ˮ.c
�ļ���ʶ��
ժ	  Ҫ��ÿƿ��ˮ1Ԫ��������ƿ�����û�һƿ��ˮ��
		  ����20Ԫ������ܺȶ���ƿ��ˮ

��ǰ�汾��
��    �ߣ�ʯ����
������ڣ�2016/11/04
*/

#include <stdio.h>

int drink_count(float cash, const float price)
{
	int empty_bottles = 0;
	int count = 0;
	while (cash >1E-10)
	{
		cash -= price;
		empty_bottles++;

		//if((empty_bottles & 1) == 0)
		if ((empty_bottles % 2) == 0)
		{
			empty_bottles++;
		}
	}

	return empty_bottles;
}

int main()
{
	float cash = 20.0;
	float price = 1.0;

	int count = 0;

	count = drink_count(cash, price);
	
	printf("count = %d\n", count);

	return 0;
}