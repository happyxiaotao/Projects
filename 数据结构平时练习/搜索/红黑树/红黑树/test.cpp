#include "RBTree.hpp"

int main()
{
	int a[] = { 10,85,15,70,20,60,30,50,65,80,90,40,5,55 };
	//int a[] = { 10, 7, 8, 15, 5, 6, 11, 13, 12 };
	//int a[] = { 1,10,120,3333,51234,123,4123,41,2,3,4,1,23,4,1,23,41,2,34,123,2,3,4,5,6,7,8,9,10 };
	RBTree<int, int> t;
	size_t size = sizeof(a) / sizeof(a[0]);
	for (int i = 0; i < size; ++i)
	{
		if (80 == a[i])//运行到某一特定情况
		{
			cout << "11" << endl;
		}
		t.Insert(a[i], 0);
	}

	t.InOrder();

	if (t.CheckRBTree())
		cout << "满足红黑树条件" << endl;
	system("pause");
	return 0;
}