#include <stdio.h>
#include <assert.h>

//Ê±¼ä¸´ÔÓ¶ÈO(N)
int MaxSubSequenceSum(const int a[], int n)
{
	int maxSum = 0;
	int thisSum = 0;
	int i = 0;
	
	assert(a);
	assert(n > 0);

	for (; i < n; ++i)
	{
		thisSum += a[i];

		if (thisSum > maxSum)
			maxSum = thisSum;
		else if (thisSum < 0)
			thisSum = 0;
	}

	return maxSum;
}

int main()
{
	int a[10] = {-1,2,3,-5,1,3,-5,10,-2,4};

	int sum = MaxSubSequenceSum(a, 10);

	printf("sum = %d\n", sum);	

	return 0;
}