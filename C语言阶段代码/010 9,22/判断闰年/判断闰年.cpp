/*
#include <stdio.h>
int main()
{	
	int min=1000,max=2000;
	int i;
	printf("�ж�1000��-2000��֮������꣺\n");
	for(i=min;i<=max;i++)
		if(i%400==0)
			printf("\t%d�������ꡣ\n",i);
		else if((i%4==0)&&(i%100!=0))
			printf("\t%d�������ꡣ\n",i);
	return 0;
}*/
/*�ж�1000��~2000��֮�������*/
/*���ף��ж�min��~max��֮�������*/
#include <stdio.h>
#include <stdlib.h>
int main()
{
	int min = 1000, max = 2000;
	int year = 0;
	int count = 0;

	/*�ж���С�����Ƿ�Ϊ4�ı��������Ǿ���Ϊ4�ı���*/

	if(min % 4 != 0)
		min = min + 4 - min % 4;
	printf("min = %d",min);

	for(year = min; year <= max; year += 4)
	{
		if(year % 100 == 0 && year % 400 != 0)
			continue ;
		printf("%d������\n",year);
		count ++;
	}
	printf("���������count = %d",count);
	system("pause");
	return 0;
}