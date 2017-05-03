/*
利用树的自相似性，可以通过递归来较好的实现树的相关功能
利用栈来存储路径
*/
#pragma once
#ifndef _BINARYTREE_H_
#define _BINARYTREE_H_

#include <iostream>
#include <queue>
#include <stack>
using namespace std;

template <typename T>
struct BinaryTreeNode
{
	BinaryTreeNode(const T& data)
		:m_data(data)
		, m_pLeft(NULL)
		, m_pRight(NULL)
	{}
	T m_data;
	BinaryTreeNode<T>* m_pLeft;//左孩子
	BinaryTreeNode<T>* m_pRight;//右孩子
};

template <typename T>
class BinaryTree//将成员函数的实现进行简单的封装，用户只能显示调用公共接口
{
	typedef BinaryTreeNode<T> Node;
public:
	BinaryTree()//无参构造函数
		:m_pRoot(NULL)
	{}
	BinaryTree(const T array[], size_t size, const T& invalid)//带参构造函数
	{
		size_t index = 0;
		_CreateTree(m_pRoot, array, size, index, invalid);
	}
	BinaryTree(const BinaryTree<T>& t)//拷贝构造函数
	{
		m_pRoot = _CopyBinaryTree(t.m_pRoot);
	}
	BinaryTree<T>& operator=(const BinaryTree<T>& t)//赋值运算符重载成员函数
	{
		_Destroy(m_pRoot);
		m_pRoot = _CopyBinaryTree(t.m_pRoot);
		return *this;
	}
	~BinaryTree()//析构函数
	{
		_Destroy(m_pRoot);
	}
	void PreOrder()//前序遍历
	{
		cout << "前序遍历：";
		_PreOrder_2(m_pRoot);
		cout << endl;
	}
	void InOrder()//中序遍历
	{
		cout << "中序遍历";
		_InOrder_2(m_pRoot);
		cout << endl;
	}
	void PostOrder()//后序遍历
	{
		cout << "后序遍历";
		_PostOrder(m_pRoot);
		cout << endl;
	}
	void LevelOrder()//层序遍历
	{
		cout << "层序遍历";
		_LevelOrder(m_pRoot);
		cout << endl;
	}

	Node* GetParent(Node* x)//获取该结点的双亲结点
	{
		return _GetParent(m_pRoot, x);
	}

	Node* Find(const T& value)//找到值为value的结点
	{
		return _Find(m_pRoot, value);
	}

	Node* GetLeftChild(Node* pCur)//返回左孩子
	{
		if (pCur)
			return pCur->m_pLeft;
		return nullptr;
	}

	Node* GetRightChild(Node* pCur)//返回右孩子
	{
		if (pCur)
			return pCur->m_pRight;
		return nullptr;
	}

	size_t Height()//获取树的高度
	{
		return _Height(m_pRoot);
	}

	size_t GetLeefNode()//获取叶子结点个数
	{
		return _GetLeefNode(m_pRoot);
	}

	size_t GetKLevelNode(size_t k)//获取某一层结点个数
	{
		return _GetKLevelNode(m_pRoot, k);
	}

private:
	void _CreateTree(Node*& pRoot, const T array[], size_t size, size_t& index, const T& invalid);//创建树
	Node* _CopyBinaryTree(Node* pRoot);//拷贝树
	void _Destroy(Node*& pRoot);//清空树

	void _PreOrder_1(Node* pRoot);//递归实现：先序遍历
	void _PreOrder_2(Node* pRoot);//非递归实现：先序遍历
	void _InOrder_1(Node* pRoot);//递归实现：中序遍历
	void _InOrder_2(Node* pRoot);//费递归实现：中序遍历
	void _PostOrder(Node* pRoot);//后序遍历
	void _LevelOrder(Node* pRoot);//层序遍历

	Node* _GetParent(Node* pRoot, Node* x);//获取双亲结点
	Node* _Find(Node* pRoot, const T& value);//找到值为value的结点
	size_t _Height(Node* pRoot);//获取树的高度
	size_t _GetLeefNode(Node* pRoot);//获取叶子结点个数
	size_t _GetKLevelNode(Node* pRoot, size_t k);//获取某一层结点个数

private:
	BinaryTreeNode<T>* m_pRoot;//根结点
};

template <typename T>//创建树
void BinaryTree<T>::_CreateTree(Node*& pRoot, const T array[], size_t size, size_t& index, const T& invalid)
{
	if ((array[index] != invalid) && (index < size))
	{
		pRoot = new Node(array[index]);
		_CreateTree(pRoot->m_pLeft, array, size, ++index, invalid);
		_CreateTree(pRoot->m_pRight, array, size, ++index, invalid);
	}
}

template <typename T>//拷贝树
BinaryTreeNode<T>* BinaryTree<T>::_CopyBinaryTree(Node* pRoot)
{
	Node* pNewRoot = NULL;
	if (pRoot)
	{
		pNewRoot = new Node(pRoot->m_data);
		pNewRoot->m_pLeft = _CopyBinaryTree(pRoot->m_pLeft);
		pNewRoot->m_pRight = _CopyBinaryTree(pRoot->m_pRight);
	}
	return pNewRoot;
}

template <typename T>
void BinaryTree<T>::_Destroy(Node*& pRoot)//清空树
{
	if (pRoot)
	{	
		_Destroy(pRoot->m_pLeft);
		_Destroy(pRoot->m_pRight);
		delete pRoot;
		pRoot = nullptr;
	}
}

template <typename T>
void BinaryTree<T>::_PreOrder_1(Node* pRoot)//递归实现：前序遍历
{
	if (pRoot)
	{
		cout << pRoot->m_data << " ";
		_PreOrder_1(pRoot->m_pLeft);
		_PreOrder_1(pRoot->m_pRight);
	}
}
template <typename T>
void BinaryTree<T>::_PreOrder_2(Node* pRoot)//非递归实现：前序遍历（利用栈实现）
{
	if (nullptr == pRoot)//空树
		return ;
	stack<Node*> s;
	s.push(pRoot);

	while (!s.empty())
	{
		Node* pTemp = s.top();
		cout << pTemp->m_data << " ";
		s.pop();//pop放在push之前，由于栈的LIFO特性

		if (pTemp->m_pRight)
			s.push(pTemp->m_pRight);//一定要先存入右子树，后存入左子树，因为栈的LIFO特性
		if (pTemp->m_pLeft)
			s.push(pTemp->m_pLeft);
	}
}

template <typename T>
void BinaryTree<T>::_InOrder_1(Node* pRoot)//递归实现：中序遍历
{
	if (pRoot)
	{
		_InOrder_1(pRoot->m_pLeft);
		cout << pRoot->m_data << " ";
		_InOrder_1(pRoot->m_pRight);
	}
}
template <typename T>
void BinaryTree<T>::_InOrder_2(Node* pRoot)//非递归实现：中序遍历(1,找到树最左边的节点，并保存路径 2，访问当前节点，并将其右子树作为根节点。3，重复12)
{	
	if (nullptr == pRoot)
		return;

	stack<Node*> s;
	Node* pCur = pRoot;

	while (!s.empty() || pCur)//注意：后面的条件，因为是中序遍历，当根节点出栈之后，还需遍历右子树
	{
		while (pCur)//找到最左边的叶子结点，将路径上结点入栈
		{
			s.push(pCur);
			pCur = pCur->m_pLeft;
		}

		Node* pTemp = s.top();
		cout << pTemp->m_data << " ";
		s.pop();

		pCur = pTemp->m_pRight;//进入右子树
	}
}

template <typename T>
void BinaryTree<T>::_PostOrder(Node* pRoot)//后序遍历
{
	if (pRoot)
	{
		_PostOrder(pRoot->m_pLeft);
		_PostOrder(pRoot->m_pRight);
		cout << pRoot->m_data << " ";
	}
}

template <typename T>
void BinaryTree<T>::_LevelOrder(Node* pRoot)//层序遍历(利用队列实现)
{	/*
	画图理解：
	1，先将根节点入队列，
	2，进入循环，队首结点出队列，输出其值。
	3，将其左右孩子节点入队列，
	4，进行2-3循环，直到队列为空
	*/
	if (!pRoot)
		return;

	queue<Node*> q;
	q.push(pRoot);

	while (!q.empty())
	{
		Node* pCur = q.front();
		q.pop();
		cout << pCur->m_data << " ";
		
		if (pCur->m_pLeft)
			q.push(pCur->m_pLeft);

		if (pCur->m_pRight)
			q.push(pCur->m_pRight);
	}
}

template <typename T>
BinaryTreeNode<T>* BinaryTree<T>::_GetParent(Node* pRoot, Node* x)//递归实现：获取双亲结点
{
	if ((nullptr == pRoot) || (pRoot == x))//空树或者该结点是根结点，没有双亲结点，返回nullptr
		return nullptr;

	if ((pRoot->m_pLeft == x) || (pRoot->m_pRight == x))//若x是根结点个左右孩子，返回该根结点
		return pRoot;
	//以上两条判断语句是递归出口
	
	//利用递归，将问题变为在左右子树中寻找x的双亲结点
	Node* parent = nullptr;
	if (parent = _GetParent(pRoot->m_pLeft, x))//左子树中寻找
		return parent;
	if (parent = _GetParent(pRoot->m_pRight, x))//右子树中寻找
		return parent;

	return nullptr;//在左右子树中未找到x的双亲结点。
}

template <typename T>
BinaryTreeNode<T>* BinaryTree<T>::_Find(Node* pRoot, const T& value)//递归实现：找到值为value的结点
{
	if (nullptr == pRoot)//空树或空结点
		return nullptr;
	
	if (pRoot->m_data == value)
		return pRoot;
	//以上两条语句是递归出口

	//利用递归，将问题变为在左右子树中寻找值为value的节点
	Node* p_node = nullptr;
	if (p_node = _Find(pRoot->m_pLeft, value))//左子树中寻找
		return p_node;
	if (p_node = _Find(pRoot->m_pRight, value))//右子树中寻找
		return p_node;

	return nullptr;//在左右子树中未找到值为value的结点。
}

template <typename T>
size_t BinaryTree<T>::_Height(Node* pRoot)//递归实现：获取树的高度
{
	if (nullptr == pRoot)//空树或空节点
		return 0;
	//以上语句为递归出口

	//利用递归：获取左右子树的高度，并将左右子树的高度中较大的高度加1，返回（当前树的pRoot不为空，所以加1）
	size_t h_left = _Height(pRoot->m_pLeft);//获得左子树高度
	size_t h_right = _Height(pRoot->m_pRight);//获得右子树高度

	return h_left > h_right ? h_left + 1 : h_right + 1;//返回树的高度
}

template <typename T>
size_t BinaryTree<T>::_GetLeefNode(Node* pRoot)//递归实现：获取叶子结点个数
{
	if (nullptr == pRoot)//空树或空结点
		return 0;
	if ((nullptr == pRoot->m_pLeft) && (nullptr == pRoot->m_pRight))//当前节点时叶子结点
		return 1;
	//以上两个判断语句是递归出口

	//利用递归，获取左右子树的叶子结点个数
	size_t leaves_left = _GetLeefNode(pRoot->m_pLeft);//获取左子树叶子结点数
	size_t leaves_right = _GetLeefNode(pRoot->m_pRight);//获取右子树叶子结点数

	return leaves_left + leaves_right;//返回左右子树叶子结点之和
}

template <typename T>
size_t BinaryTree<T>::_GetKLevelNode(Node* pRoot, size_t k)//递归实现：获取某一层结点个数
{
	if ((nullptr == pRoot) || (1 > k))//空树或空结点、k小于1
		return 0;
	if (1 == k)//k=1表示当前结点
		return 1;
	//以上两个判断语句是递归出口

	//利用递归，获取左右子树中处于k-1层结点个数
	size_t nodes_left = _GetKLevelNode(pRoot->m_pLeft, k - 1);//获取左子树中k-1层结点个数
	size_t nodes_right = _GetKLevelNode(pRoot->m_pRight, k - 1);//获取右子树中k-1层结点个数

	return nodes_left + nodes_right;
}

#endif //_BINARYTREE_H_