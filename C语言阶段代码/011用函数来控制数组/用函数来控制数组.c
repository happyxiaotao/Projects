#include <stdio.h>
#include <stdlib.h>

int init(int arr[], int n);
int empty(int arr[], int n);
int reverse(int arr[], int n);
void exchange(int* a, int* b);

int main()
{	
	int arr[10] = {0};

	printf("调用初始化函数...\n");
	printf("输入10个整数\n");
	if(init(arr, 10))
		printf("数组初始化成功！\n");

	system("pause");

	printf("调用清空数组函数...\n");
	if(empty(arr, 10))
		printf("数组清空成功！\n");

	system("pause");

	printf("调用逆置数组元素函数...\n");
	if(reverse(arr, 10))
		printf("数组元素逆置成功！\n");

	return 0;
}

int init(int arr[], int n)
{
	int i = 0;

	for(i = 0; i < n; i++)
	{
		scanf("%d",&arr[i]);
	}

	return 1;
}

int empty(int arr[], int n)
{
	int i = 0;

	for(i = 0; i < n; i++)
	{
		arr[i] = 0;
	}

	return 1;
}
int reverse(int arr[], int n)
{
	int i = 0;
	int left = 0;
	int right = n-1;

	while(left <= right)
	{
		exchange(&arr[left], &arr[right]);
		left++;
		right--;
	}

	return 1;
}

void exchange(int* a, int* b)
{	
	*a = *a + *b;
	*b = *a - *b;
	*a = *a - *b;
}