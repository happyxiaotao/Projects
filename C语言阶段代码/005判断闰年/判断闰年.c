#include <stdio.h>

int Is_leap_year(int year);

int main()
{
	int min = 1000;
	int max = 2000;
	int year = 0;
	int count = 0;

	for(year = min; year <= max; year++)
	{
		if(Is_leap_year(year))
		{
			count++;
			printf("%d\n",year);
		}
	}
	printf("count = %d\n",count);
	return 0 ;
}
int Is_leap_year(int year)
{
	int flag = (year%400==0 || (year%4==0 && year%100!=0));
	return flag;
}