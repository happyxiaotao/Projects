#include <stdio.h>

void exchange(int* a, int* b);

int main()
{
	int a = 10;
	int b = 20;
	
	printf("Original: a = %d, b = %d\n",a, b);

	exchange(&a, &b);

	printf("Now: a = %d, b = %d\n",a, b);

	return 0;
}
void exchange(int* a, int* b)
{	
	*a = *a + *b;
	*b = *a - *b;
	*a = *a - *b;
	/*
	*a = *a ^ *b;
	*b = *a ^ *b;
	*a = *a ^ *b;
	*/
}