/*
目标：利用二叉树存储一个后缀表达式（类似于语法分析树类似《程序员的自我修养》
需要的适配器：栈

对二叉树的中序遍历结果是：中缀表达式
对二叉树的后序遍历结果是：后缀表达式
*/
#include <iostream>
#include <stack>
using namespace std;

struct BinaryTreeNode
{
	BinaryTreeNode(char value)
		:m_value(value)
		, m_pLeft(nullptr)
		, m_pRight(nullptr)
	{}
	char m_value;
	BinaryTreeNode* m_pLeft;
	BinaryTreeNode* m_pRight;
};

class BinaryTree
{
	typedef BinaryTreeNode Node;
public:
	BinaryTree()
		:m_pRoot(nullptr)
	{}
	BinaryTree(char* array, size_t size)
	{
		_CreateBinaryTree();
	}
private:
	void _CreateBinaryTree();
private:
	Node* m_pRoot;
};

int main()
{
	return 0;
}