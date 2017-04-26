#pragma once
#ifndef _BINARYTREE_H_
#define _BINARYTREE_H_

#include <iostream>
#include <queue>
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
class BinaryTree
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
		_PreOrder(m_pRoot);
		cout << endl;
	}
	void InOrder()//中序遍历
	{
		cout << "中序遍历";
		_InOrder(m_pRoot);
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

private:
	void _CreateTree(Node*& pRoot, const T array[], size_t size, size_t& index, const T& invalid);//创建树
	Node* _CopyBinaryTree(Node* pRoot);//拷贝树
	void _Destroy(Node*& pRoot);//清空树
	void _PreOrder(Node* pRoot);//先序遍历
	void _InOrder(Node* pRoot);//中序遍历
	void _PostOrder(Node* pRoot);//后序遍历
	void _LevelOrder(Node* pRoot);//层序遍历

private:
	BinaryTreeNode<T>* m_pRoot;
};

template <typename T>
void BinaryTree<T>::_CreateTree(Node*& pRoot, const T array[], size_t size, size_t& index, const T& invalid)
{
	if ((array[index] != invalid) && (index < size))
	{
		pRoot = new Node(array[index]);
		_CreateTree(pRoot->m_pLeft, array, size, ++index, invalid);
		_CreateTree(pRoot->m_pRight, array, size, ++index, invalid);
	}
}

template <typename T>
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
void BinaryTree<T>::_PreOrder(Node* pRoot)//前序遍历
{
	if (pRoot)
	{
		cout << pRoot->m_data << " ";
		_PreOrder(pRoot->m_pLeft);
		_PreOrder(pRoot->m_pRight);
	}
}

template <typename T>
void BinaryTree<T>::_InOrder(Node* pRoot)//中序遍历
{
	if (pRoot)
	{
		_InOrder(pRoot->m_pLeft);
		cout << pRoot->m_data << " ";
		_InOrder(pRoot->m_pRight);
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

#endif //_BINARYTREE_H_