#include <stdio.h>

void Output_bit(int value)
{
	int divisor = 0;
	
	if (0 > value)//value是负数
	{
		printf("-");
		value *= -1;
	}
	
	divisor = value % 10
	value /= 10;

	if(value)
	{
		Output_bit(value);
	}

	printf("%d ", divisor);
}

int main()
{
	int value = 152213;
	
	Output_bit(value);

	return 0;
}
