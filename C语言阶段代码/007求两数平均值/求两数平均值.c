#include <stdio.h>
int main()
{
	int a = 9;
	int b = 6;

	int average1 = b - ((a - b)>>1);//不能使用a - ((a-b)>>1),求得的值会大1
	int average2 = (a & b) + ((a ^ b)>>1);
	int average3 = (a + b) >> 1;

	printf("a = %d, b = %d, average = b + ((a - b)>>1) = %d\n",a, b, average1);
	printf("a = %d, b = %d, average = (a & b) + ((a ^ b)>>1) = %d\n",a, b, average2);
	printf("a = %d, b = %d, average = (a + b) >> 1 = %d\n",a, b, average3);
}