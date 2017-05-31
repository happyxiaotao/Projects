#include <stdio.h>

int main()
{
	int a = 1999;
	int b = 2299;
	int tmp = a^b;
	int count = 0;

	while(tmp)
	{
		if(tmp%2)//1 == tmp%2
			++count;
		tmp >>= 1;
	}

	printf("count = %d\n",count);

	return 0;
} 