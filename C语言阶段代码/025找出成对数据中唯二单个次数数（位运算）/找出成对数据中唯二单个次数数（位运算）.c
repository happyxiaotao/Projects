
/*
Copyrights (c) 2016,���ƴ�8555ʯ����
All rights resverse

�ļ����ƣ�test.c
�ļ���ʶ��000
ժ    Ҫ����һ�����֣�����������ֻ������һ�Σ��������ֶ��ǳɶ�
		  ���ֵģ����ҳ�������֡�

��ǰ�汾��1.0
��    �ţ�ʯ����
������ڣ�2016/10/31
*/
#include <stdio.h>

int main()
{
	int arr[] = {1, 1, 10, 2, 2, 5, 5, 8, 7, 7, 10, 10};
	int sz = sizeof(arr)/sizeof(int);
	int i = 0;
	int ret = 0;
	int bit_0 = 0;
	int bit_1 = 0;
	int count = 0;

	for (i = 0; i < sz; i++)
	{
		ret ^= arr[i];
	}

	while ((ret&1) != 1)
	{	
		count++;
 
		ret >>= 1;
	}
	
	for (i = 0; i < sz; i++)
	{
		if ((arr[i]>>count)&1)
		{
			bit_1 ^= arr[i];
		}
		else
		{
			bit_0 ^= arr[i];
		}
	}

	printf("�������������ε�����m = %d, n = %d\n", bit_0, bit_1);

	return 0;
}