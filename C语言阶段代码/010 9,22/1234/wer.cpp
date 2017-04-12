#include <stdio.h>
int main()
{
	int year;
	int count = 0;

	for(year = 1000; year <= 2000; year+=4)
	{
		if(year % 100 == 0 && year % 400 != 0)
			;
		else 
		{
			printf("\t%d\n",year);
			count ++ ;
		}
	}

	printf("ÈòÄê¸öÊıcount = %d\n",count);

	return 0;

}