/*
Ŀ�꣺���ö������洢һ����׺���ʽ���������﷨���������ơ�����Ա������������
��Ҫ����������ջ

�Զ������������������ǣ���׺���ʽ
�Զ������ĺ����������ǣ���׺���ʽ
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