/*
输入一个整数数组，实现一个函数来调整该数组中数字的顺序，使得所有的奇数位于数组的前半部分，
所有的偶数位于位于数组的后半部分，并保证奇数和奇数，偶数和偶数之间的相对位置不变。
*/
void reOrderArray(int arr[], int sz)
{	
	int new_arr[sz];
	int i = 0;
	int j = 0;
	for (; i < sz; i++)
		if (arr[i]%2 == 1)
			new_arr[j++] = arr[i];

	for (i = 0; i < sz; i++)
		if (arr[i]%2 == 0)
			new_arr[j++] = arr[i];

	for (i = 0; i < sz; i++)
		arr[i] = new_arr[i];
}
int main()
{
	int arr[10] = {1,2,3,4,5,6,7,8,9,10};
	reOrderArray(arr, 10);
	return 0;
}