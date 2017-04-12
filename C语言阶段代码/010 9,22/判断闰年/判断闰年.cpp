/*
#include <stdio.h>
int main()
{	
	int min=1000,max=2000;
	int i;
	printf("判断1000年-2000年之间的闰年：\n");
	for(i=min;i<=max;i++)
		if(i%400==0)
			printf("\t%d年是闰年。\n",i);
		else if((i%4==0)&&(i%100!=0))
			printf("\t%d年是闰年。\n",i);
	return 0;
}*/
/*判断1000年~2000年之间的闰年*/
/*进阶：判断min年~max年之间的闰年*/
#include <stdio.h>
#include <stdlib.h>
int main()
{
	int min = 1000, max = 2000;
	int year = 0;
	int count = 0;

	/*判断最小的数是否为4的倍数，不是就置为4的倍数*/

	if(min % 4 != 0)
		min = min + 4 - min % 4;
	printf("min = %d",min);

	for(year = min; year <= max; year += 4)
	{
		if(year % 100 == 0 && year % 400 != 0)
			continue ;
		printf("%d是闰年\n",year);
		count ++;
	}
	printf("闰年个数是count = %d",count);
	system("pause");
	return 0;
}