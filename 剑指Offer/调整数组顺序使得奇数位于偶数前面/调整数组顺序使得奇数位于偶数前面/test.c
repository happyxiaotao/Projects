/*
����һ���������飬ʵ��һ�����������������������ֵ�˳��ʹ�����е�����λ�������ǰ�벿�֣�
���е�ż��λ��λ������ĺ�벿�֣�����֤������������ż����ż��֮������λ�ò��䡣
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