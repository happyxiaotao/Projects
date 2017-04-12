#include <stdio.h>
int  count_one_bits(unsigned int value)
{
	int count = 0;
/*
	while(value)
	{
		if(value & 1)
		{
			count++;
		}

		value >>= 1;
	}
*/
	while(value)
	{
		value = value & (value-1);
		count++;
	}
	return count;
}
int main()
{
	unsigned int value = 15;
	int count = 0;

	count = count_one_bits(value);

	printf("count = %d\n",count);

	return 0;
}