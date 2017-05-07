#pragma once
#ifndef _BINARYTREETH_H_
#define _BINARYTREETH_H_

#include <iostream>
using namespace std;

enum PointFlag {LINK, THREAD};//设表示指针域所指对象表示的含义
template <typename T>
class BinaryTreeThNode
{
public:
	BinaryTreeThNode(const T& data)
		:_data(data)
		, _pLeft(nullptr)
		, _pRight(nullptr)
		,_leftThread(LINK)
		,_rightThread(LINK)
	{}
public:
	T _data;
	BinaryTreeThNode<T>* _pLeft;
	BinaryTreeThNode<T>* _pRight;
	PointFlag _leftThread;
	PointFlag _rightThread;
};

template <typename T>
class BinaryTreeTh
{
	typedef BinaryTreeThNode<T> Node;
public:
	BinaryTreeTh()
		: _pRoot(nullptr)
	{}
	
	BinaryTreeTh(const T array[], size_t size, const T& invalid)//创建普通二叉树
	{
		size_t index = 0;
		_CreateTree(_pRoot, array, size, index, invalid);
	}

	void PreThreading()//前序线索化二叉树
	{
		Node* prev = nullptr;
		_PreThreading(_pRoot, prev);
	}

	void InThreading()//中序线索化二叉树
	{
		Node* prev = nullptr;
		_InThreading(_pRoot, prev);
	}

	void PostThreading()//后序线索化二叉树
	{
		Node* prev = nullptr;
		_PostThreading(_pRoot, prev);
	}

	void PreOrder();//前序遍历线索二叉树

	void InOrder();//中序遍历线索二叉树

	void PostOrder();//后序遍历线索二叉树

private:
	void _CreateTree(Node* &pRoot, const T array[], size_t size, size_t& index, const T& invalid);//创建二叉树

	void _PreThreading(Node* pRoot, Node*& prev);//前序线索化二叉树

	void _InThreading(Node* pRoot, Node*& prev);//中序线索化二叉树

	void _PostThreading(Node* pRoot, Node*& prev);//后序线索化二叉树
private:
	Node* _pRoot;
};


template <typename T>//创建二叉树
void BinaryTreeTh<T>::_CreateTree(Node*& pRoot, const T array[], size_t size, size_t& index, const T& invalid)
{
	if ((index < size) && (array[index] != invalid))
	{
		pRoot = new Node(array[index]);

		_CreateTree(pRoot->_pLeft, array, size, ++index, invalid);
		_CreateTree(pRoot->_pRight, array, size, ++index, invalid);
	}
}

template <typename T>//前序线索化二叉树
void BinaryTreeTh<T>::_PreThreading(Node* pRoot, Node*& prev)
{
	/*
	对于前序遍历线索化二叉树。（前序遍历顺序：根-左-右。线索化顺序：根-左-右）
	某一结点：
		左指针域：左孩子（非空）/前驱（空）
		右指针域：右孩子（非空）/后继（空）
	*/

	if (pRoot)
	{
		if (prev && (nullptr == pRoot->_pLeft))//当左孩子为空时，线索化左孩子（prev不能为空）
		{
			pRoot->_pLeft = prev;
			pRoot->_leftThread = THREAD;
		}
		if (prev && (nullptr == prev->_pRight))//当右孩子为空时，线索化右孩子（prev不能为空）
		{
			prev->_pRight = pRoot;
			prev->_rightThread = THREAD;
		}
		
		prev = pRoot;//prev指向最近访问的结点

		if (LINK == pRoot->_leftThread)//左孩子未进行线索化（即左孩子不为空），进入左孩子所在树，进行线索化
			_PreThreading(pRoot->_pLeft, prev);

		if (LINK == pRoot->_rightThread)//右孩子未进行线索化（即右孩子不为空），进入右孩子所在树，进行线索化
			_PreThreading(pRoot->_pRight, prev);
	}
}

#endif //_BINARYTREETH_H_