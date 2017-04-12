#include <stdio.h>

int main()
{
	int arr[7] = {1,3,5,7,5,3,1};
	int i = 0;
	int single = 0;

	for(i = 0; i < 7; i++)
	{
		single ^= arr[i];
	}

	printf("single = %d\n",single);

	return 0;
}