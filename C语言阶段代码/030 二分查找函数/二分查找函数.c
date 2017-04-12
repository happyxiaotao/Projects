
/*
Copyrights (c) 2016, 西科大8555室石俊涛
All rights reverse

文件名称：030 二分查找函数.c
文件标识：
摘	  要：二分查找函数

当前版本：
作    者：石俊涛
完成日期：2016/11/04
*/
#include <stdio.h>

/**/
int Bin_Search(const int arr[], int sz, int key)
{
	int left = 0;
	int right = sz-1;
	int ret = -1;

	while (left <= right)
	{
		int mid = left+((right-left)>>1);

		if (arr[mid] > key)
		{
			right = mid-1;
		}
		else if (arr[mid] < key)
		{
			left = mid+1;
		}                                                                                                                                                                                                                                                                                                                                                                                  
		else if (arr[mid] == key)
		{
			ret = mid;

			break;
		}
	}

	return ret;
}
/*采用不对称边界和指针解法
int *BSearch(const int *arr, int sz, int key)
{
	int *left = arr;
	int *right = arr+sz;

	assert(arr != NULL);

	while (left < right)
	{
		int *mid = left + ((right - left) >> 1);
		int *ret = arr + mid;

		if (*(arr+mid) > key)
		{
			right = mid;
		}
		else if (*(arr+mid) < key)
		{
			left = mid + 1;
		}
		else
		{
			return ret;
		}
	}

	return NULL;
}*/
int main()
{
	int arr[] = {1,15,16,44,123,616,2000,5235,9000,10000,20000}; 
	int sz = sizeof(arr)/sizeof(arr[0]);
	int key = 0;
	int ret = -1;

	printf("input key = ");
	scanf("%d", &key);

	ret = Bin_Search(arr, sz, key);

	if (ret != -1)
	{
		printf("查找成功！数组下标是：%d\n", ret);
	}
	else
	{
		printf("查找失败！\n");
	}

	return 0;
}
