#include <stdio.h>

int main()
{
	int min = 1;
	int max = 4;

	int i = 0;

	float flag = 1;

	double sum = 0;

	for(i = min; i <= max; i++)
	{
		sum += flag/i;
		flag = -flag;
	}
	
	printf("sum = %lf\n",sum);

	return 0;
}