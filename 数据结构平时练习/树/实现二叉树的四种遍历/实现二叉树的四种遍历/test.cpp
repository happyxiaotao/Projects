#include "BinaryTree.hpp"

//按照二叉树的先序遍历存入字符串中
char* array1 = "124###35##6";
char* array2 = "124##5##3#6";

int main()
{
	BinaryTree<char> t1(array1, strlen(array1), '#');
	BinaryTree<char> t2(array2, strlen(array2), '#');

	//	t1.PreOrder();
	//	t1.InOrder();
	//	t1.PostOrder();
	//t1.LevelOrder();

	//	t2.PreOrder();
	//	t2.InOrder();
	//	t2.PostOrder();
	//t2.LevelOrder();

	BinaryTree<char> t3;
	t3 = t2;
	t3.PreOrder();
	t3.InOrder();
	t3.PostOrder();
	t3.LevelOrder();


	system("pause");
	return 0;
}