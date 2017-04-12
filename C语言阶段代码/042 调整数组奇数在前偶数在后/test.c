#include <stdio.h>

void Odd_before(int *arr, int sz)
{
	int *left = arr;
	int *right = arr + sz -1;

	while (left < right)
	{
		while (1 == (*left&1))//注意运算符的优先级
		{
			++left;
		} 

		while (1 != (*right&1))
		{
			--right;
		}

		if ( left < right)
		{
			int tmp = *left;
			*left = *right;
			*right = tmp;
		}
	}
}

int main()
{
	int arr[10] = {1,4,6,6,3,12,5,6,41,14,};

	int sz = sizeof(arr)/sizeof(arr[0]);
	int i  = 0;

	Odd_before(arr, sz);

	for (i = 0; i < sz; i++)
	{
		printf("%2d : %d\n", i, arr[i]);
	}

	return 0;
}