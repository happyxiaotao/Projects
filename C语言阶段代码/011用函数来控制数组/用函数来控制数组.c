#include <stdio.h>
#include <stdlib.h>

int init(int arr[], int n);
int empty(int arr[], int n);
int reverse(int arr[], int n);
void exchange(int* a, int* b);

int main()
{	
	int arr[10] = {0};

	printf("���ó�ʼ������...\n");
	printf("����10������\n");
	if(init(arr, 10))
		printf("�����ʼ���ɹ���\n");

	system("pause");

	printf("����������麯��...\n");
	if(empty(arr, 10))
		printf("������ճɹ���\n");

	system("pause");

	printf("������������Ԫ�غ���...\n");
	if(reverse(arr, 10))
		printf("����Ԫ�����óɹ���\n");

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