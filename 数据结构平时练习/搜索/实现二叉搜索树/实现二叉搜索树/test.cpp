#include "BST.hpp"

void Test1();
void Test2();

int main()
{
	Test1();

	system("pause");
	return 0;
}

void Test1()
{
	int arr[5] = { 1,3,5,2,4 };
	BinarySearchTree<int, int> bst;

	for (int i = 0; i < 5; ++i)
		bst.Insert(arr[i], 0);

	bst.InOrder();

	for (int i = 0; i < 6; ++i)
	{
		bst.Remove_Nor(i);
		bst.InOrder();
	}
}

void Test2()
{
	int arr = 1;
	
	BinarySearchTree<int, int> bst;

	bst.Insert(1, 0);
	bst.InOrder();

	bst.Remove_Nor(1);

	bst.InOrder();
}
