#include "BSTaddIterator.hpp"
#include <iostream>
using namespace std;

void Test1();
void Test2();
void Test3();


void Test4()
{
	BinarySearchTree<int, int> bst;
	
	BinarySearchTree<int, int>::iterator it;
	it = bst.Begin();
	cout << it->_key << endl;
}

int main()
{
	Test4();
	

	system("pause");
	return 0;
}

void Test1()
{
	int arr[5] = { 1,3,5,2,4 };
	BinarySearchTree<int, int> bst;

	for (int i = 0; i < 5; ++i)
		bst.Insert_Nor(arr[i], 0);

	bst.InOrder();

	bst.Remove_Nor(2);
	bst.InOrder();

	bst.Remove_Nor(1);
	bst.InOrder();

	bst.Remove_Nor(5);
	bst.InOrder();

	bst.Remove_Nor(3);
	bst.InOrder();

	bst.Remove_Nor(4);
	bst.InOrder();

	bst.InOrder();
}

void Test2()
{
	int arr = 1;
	
	BinarySearchTree<int, int> bst;

	bst.Insert_Nor(1, 0);
	bst.InOrder();

	bst.Remove_Nor(1);

	bst.InOrder();
}

void Test3()
{
	int arr[10] = { 1,3,5,7,9,2,4,6,8,10 };

	BinarySearchTree<int, int> bst;

	BinarySearchTree<int, int>::iterator it;

	for (int i = 0; i < 10; ++i)
		bst.Insert_Nor(arr[i], 0);
	
	
	it = bst.Begin();

	while (it != bst.End())
	{
		cout << it->_key << " ";
		++it;
	}
	cout << endl;

	for (int i = 0; i < 10; ++i)
		bst.Remove_Nor(i+1);

	BSTNode<int, int>* pHead = bst.ToList();

	while (pHead)
	{
		cout << pHead->_key << " ";
		pHead = pHead->_pRight;
	}

	cout << endl;
}