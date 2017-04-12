#include <stdio.h>

int main()
{
	int tmp = 0;
	
	while((tmp = getchar()) != EOF)
	{
		if(tmp >= 48 && tmp <= 57)
			continue;
		else if(tmp >= 65 && tmp <=90)
			tmp += 32;
		else if(tmp >= 97 && tmp <= 122)
			tmp -= 32;

		putchar(tmp);
	}

	return 0;
}