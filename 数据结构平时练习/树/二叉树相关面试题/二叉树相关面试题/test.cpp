#include "BinaryTree.hpp"

//按照二叉树的先序遍历存入字符串中
char* array1 = "124###35##6";
char* array2 = "124##5##3#6";

BinaryTree<char> t1(array1, strlen(array1), '#');

void FunTest1();
void FunTest2();

int main()
{
	FunTest2();

	system("pause");
	return 0;
}
void FunTest1()
{
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
	//	t3.PreOrder();
	//	t3.InOrder();
	//	t3.PostOrder();
	//	t3.LevelOrder();
}

void FunTest2()
{
	typedef BinaryTreeNode<char>* PNode;
	PNode node_1(0), node_2(0), node_3(0), node_4(0), node_5(0), node_6(0);

	//获取值为value的结点
	node_1 = t1.Find('1');
	node_2 = t1.Find('2');
	node_3 = t1.Find('3');
	node_4 = t1.Find('4');
	node_5 = t1.Find('5');
	node_6 = t1.Find('6');

	////获取树的双亲结点
	//cout << t1.GetParent(node_1) << endl;
	//cout << t1.GetParent(node_2)->m_data << endl;
	//cout << t1.GetParent(node_3)->m_data << endl;
	//cout << t1.GetParent(node_4)->m_data << endl;
	//cout << t1.GetParent(node_5)->m_data << endl;
	//cout << t1.GetParent(node_6)->m_data << endl;

	//获取树的高度
	//cout << t1.Height() << endl;

	//获取叶子结点个数
	//cout << t1.GetLeefNode() << endl;

	//获取某一层结点个数
	//cout << t1.GetKLevelNode(3) << endl;

	//打印镜像
	t1.GetBinaryMirror_Nor();
	//t1.GetBinaryMirror();
	//t1.PreOrder();
	//t1.InOrder();
	//t1.PostOrder();
	//t1.LevelOrder();

	//判断是否是完全二叉树
	{
		char* array3 = "124##5##36";
		BinaryTree<char> t1(array3, strlen(array1), '#');
		cout << t1.IsCompleteBinaryTree() << endl;
	}
}