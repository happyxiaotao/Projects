#include <stdio.h>
#include <math.h>
int main(void)
{
	int min = 100,max = 200;
	int i,j,d;
	bool flag;
	printf("100到200之间的素数列表：\n");
	for(i=min;i<=max;i++)
	{
		d = (int)sqrt(i);
		flag = true;
		for(j = 2;j<=d;j++)
			if(i%j==0)
			{
				flag = false;
				break;
			}
		if(flag)
			printf("\t%d\n",i);
	}
	return 0;
}
