#include <stdio.h>
#include <assert.h>

typedef int ElementType;
int BinarySearch(const ElementType a[], ElementType x, int n)
{
	int low = 0;
	int high = 0;

	assert(a);
	assert(n > 0);

	high = n-1;

	while (low <= high)
	{
		int mid = (low&high)+((low^high)>>1);
		
		if (a[mid] > x)
			high = mid-1;
		else if (a[mid] < x)
			low = mid+1;
		else
			return mid;
	}

	return -1;
}

int main()
{
	int a[10] = {1,3,5,5,10,20,21,212,2342,12351};
	int index = BinarySearch(a, 10, 10);

	printf("index = %d\n", index);

	return 0;
}