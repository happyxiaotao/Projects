#include "RBTree.hpp"

int main()
{
	int a[] = { 10, 7, 8, 15, 5, 6, 11, 13, 12 };
	RBTree<int, int> t;
	size_t size = sizeof(a) / sizeof(a[0]);
	for (int i = 0; i < size; ++i)
	{
		t.Insert(a[i], 0);
	}

	t.InOrder();

	t.CheckRBTree();

	system("pause");
	return 0;
}