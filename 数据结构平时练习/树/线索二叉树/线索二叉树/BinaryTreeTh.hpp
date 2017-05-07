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
private:
	T _data;
	BinaryTreeThNode<T>* _pLeft;
	BinaryTreeThNode<T>* _pRight;
	PointFlag _leftThread;
	PointFlag _rightThread;
};

template <typename T>
class BinaryTreeTh
{
	typedef BinaryTreeThNode Node;
public:
	BinaryTreeTh()
		: _pRoot(nullptr)
	{}
	
	BinaryTreeTh(const T array[], size_t size, const T& invalid)//创建普通二叉树
	{
		size_t index = 0;
		_CreateTree(_pRoot, array, size, index, invalid);
	}

	void PreThreading()//前序遍历线索化二叉树
	{
		Node* prev = nullptr;
		_PreThreading(_pRoot, prev);
	}

	void InThreading()//中序遍历线索化二叉树
	{
		Node* prev = nullptr;
		_InThreading(_pRoot, prev);
	}

	void PostThreading()//后序遍历线索化二叉树
	{
		Node* prev = nullptr;
		_PostThreading(_pRoot, prev);
	}

	void PreOrder();//前序遍历线索二叉树

	void InOrder();//中序遍历线索二叉树

	void PostOrder();//后序遍历线索二叉树

private:
	void _CreateTree(Node* &pRoot, const T array[], size_t size, size_t& index, const T& invalid);//创建二叉树

	void _PreThreading(Node* pRoot, Node*& prev);//前序遍历线索化二叉树

	void _InThreading(Node* pRoot, Node*& prev);//中序遍历线索化二叉树

	void _PostThreading(Node* pRoot, Node*& prev);//后序遍历线索化二叉树
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

#endif //_BINARYTREETH_H_