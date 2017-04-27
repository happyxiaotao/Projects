/*
Ŀ�꣺ʹ�ö������洢һ����׺���ʽ���������﷨���������ơ�����Ա������������
��Ҫ�����ݽṹ��ջ���Զ�����������
�ο��������ݽṹ���㷨����C++�����������İ桷P106
������Ҫ��ʱ��׺���ʽ�������ǰ׺�Ļ������Բο���һ�εĶ���������ʵ�ֶ����������ֱ�����

�Զ���������������������Ž���ǣ���׺���ʽ
�Զ������ĺ����������ǣ���׺���ʽ

��չ������ģ��ʵ�֣��ο��������������ʹ��һ���ṹ�������棬������һ���ṹ�����飩
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

class BinaryTree//������ʵ�ַ��룬�����û�����
{
	typedef BinaryTreeNode Node;
public:
	BinaryTree()
		:m_pRoot(nullptr)
	{}
	BinaryTree(const char* array, size_t size);
	void InOrder()
	{
		cout << "�������" << endl;
		_InOrder(m_pRoot);
		cout << endl;
	}
	void PostOrder()
	{
		cout << "�������" << endl;
		_PostOrder(m_pRoot);
		cout << endl;
	}
private:
	bool isOperator(char ch)
	{
		if (('+' == ch) || ('-' == ch) || ('*' == ch) || ('/' == ch))
			return true;
		
		return false;
	}
	void _InOrder(Node* pRoot);
	void _PostOrder(Node* pRoot);
private:
	Node* m_pRoot;
};
BinaryTree::BinaryTree(const char* array, size_t size)
{
	if (nullptr == array)
	{
		m_pRoot = nullptr;
		return ;
	}
	stack<Node*> v;

	for (int i = 0; i < size; ++i)
	{
		Node* pNewNode = new Node(array[i]);
		if (!isOperator(array[i]))
			v.push(pNewNode);
		else if ((isOperator(array[i])) && (1 < v.size()))
		{
			Node* pRight = v.top();
			v.pop();
			Node* pLeft = v.top();
			v.pop();

			pNewNode->m_pLeft = pLeft;
			pNewNode->m_pRight = pRight;

			v.push(pNewNode);
		}
		else
		{
			cout << "�沨�����ʽ�������" << endl;
			return;
		}
	}

	m_pRoot = v.top();
}

void BinaryTree::_InOrder(Node* pRoot)//�������
{
	if (pRoot)
	{
		if (pRoot->m_pLeft || pRoot->m_pRight)
		{
			cout << '(';
			_InOrder(pRoot->m_pLeft);
			cout << pRoot->m_value;
			_InOrder(pRoot->m_pRight);
			cout << ')';
		}
		else
		{
			_InOrder(pRoot->m_pLeft);
			cout << pRoot->m_value;
			_InOrder(pRoot->m_pRight);
		}
	}
}
void BinaryTree::_PostOrder(Node* pRoot)//�������
{
	if (pRoot)
	{
		_PostOrder(pRoot->m_pLeft);
		_PostOrder(pRoot->m_pRight);
		cout << pRoot->m_value << " ";
	}
}

//��׺���ʽ
char* array1 = "abc*+de*f+g*+";

int main()
{
	BinaryTree t(array1, strlen(array1));
	
	t.InOrder();
	t.PostOrder();

	system("pause");
	return 0;
}