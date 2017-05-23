#include "AVL.hpp"

#include <iostream>
using namespace std;

void Test1();

int main()
{
	Test1();

	system("pause");
	return 0;
}

void Test1()
{		
	int array[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };
	size_t size = sizeof(array) / sizeof(array[0]);

	AVLTree<int, int> avl;
	for (int i = 0; i < size; ++i)
	{
		avl.Insert(array[i], 0);
	}

	avl.InOrder();

	cout << avl.IsBalanceTree() << endl;

}