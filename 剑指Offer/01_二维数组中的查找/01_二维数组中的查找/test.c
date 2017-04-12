#include <stdio.h>

int Find(int target, int arr[][])
{

}

int main()
{
	int arr[][] = {	{1,2,3,4,5,6},
					{2,3,4,5,6,7},
					{3,4,5,6,7,8},
					{4,5,6,7,8,9},
					{5,6,7,8,9,10},
					{6,7,8,9,10,11},
					{11,12,13,14,15,16}};

	if (0 <= Find(20, arr))
	{
		printf("find success!\n");
	}
	else
	{
		printf("find fail!\n");
	}
	return 0;
}