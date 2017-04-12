#include <stdio.h>
int main(void)
{
	int i,j;
	printf("Êä³ö¾Å¾Å³Ë·¨¿Ú¾÷\n");
	for(i=1;i<=9;i++)
	{
		for(j=1;j<=i;j++)
			printf("%d*%d=%d\t",i,j,i*j);
		printf("\n");
	}
	return 0;
}