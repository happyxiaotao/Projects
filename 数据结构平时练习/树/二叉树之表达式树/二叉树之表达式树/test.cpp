/*
目标：使用二叉树存储一个后缀表达式（类似于语法分析树类似《程序员的自我修养》
需要的数据结构：栈，自定义数据类型
参考：《数据结构与算法分析C++语言描述第四版》P106
对输入要求时后缀表达式，如果是前缀的话，可以参考上一次的二叉树程序“实现二叉树的四种遍历”

对二叉树的中序遍历加上括号结果是：中缀表达式
对二叉树的后序遍历结果是：后缀表达式

扩展：利用模板实现（参考，将输入的数据使用一各结构体来保存，即传入一个结构体数组）
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

class BinaryTree//调用与实现分离，方便用户调用
{
	typedef BinaryTreeNode Node;
public:
	BinaryTree()
		:m_pRoot(nullptr)
	{}
	BinaryTree(const char* array, size_t size);
	void InOrder()
	{
		cout << "中序遍历" << endl;
		_InOrder(m_pRoot);
		cout << endl;
	}
	void PostOrder()
	{
		cout << "后序遍历" << endl;
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
			cout << "逆波兰表达式输入错误！" << endl;
			return;
		}
	}

	m_pRoot = v.top();
}

void BinaryTree::_InOrder(Node* pRoot)//中序遍历
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
void BinaryTree::_PostOrder(Node* pRoot)//后序遍历
{
	if (pRoot)
	{
		_PostOrder(pRoot->m_pLeft);
		_PostOrder(pRoot->m_pRight);
		cout << pRoot->m_value << " ";
	}
}

//后缀表达式
char* array1 = "abc*+de*f+g*+";

int main()
{
	BinaryTree t(array1, strlen(array1));
	
	t.InOrder();
	t.PostOrder();

	system("pause");
	return 0;
}