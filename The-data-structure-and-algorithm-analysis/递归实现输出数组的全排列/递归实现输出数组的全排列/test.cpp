/*
˼·������N������һ����N!�����и�����
����N����֮ǰ����֪ǰN-1������ȫ���С�
�������õݹ�ʵ�֡�
*/
#include <iostream>
using namespace std;

void perm(int* a, int k, int n)
{
	if (k == n)
	{
		for (int i = 0; i < n; ++i)
			cout << a[i] << " ";
		cout << endl;
	}
	else
	{
		for (int i = k; i <= n; ++i)
		{
			::swap(a[i-1], a[k-1]);
			perm(a, k+1, n);
			::swap(a[i-1], a[k-1]); 
		}
	}
}

int main()
{
	int a[5] = {1,2,3,4,5};
	perm(a, 3, 5);
	system("pause");
}