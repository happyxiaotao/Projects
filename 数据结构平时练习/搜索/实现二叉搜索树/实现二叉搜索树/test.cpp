#include "BST.hpp"

int main()
{
	int arr[5] = {1,3,5,2,4};
	BinarySearchTree<int, int> bst;

	for (int i = 0; i < 5; ++i)
		bst.Insert(arr[i], 0);

	bst.InOrder();

	system("pause");
	return 0;
}