#pragma once

#ifndef _BST_H_
#define _BST_H_

#include <iostream>
using namespace std;

template <typename K, typename V>
struct BSTNode
{
	BSTNode(const K& key = K(), const V& value = V())
		:_pLeft(nullptr)
		,_pRight(nullptr)
		,_key(key)
		,_value(value)
	{}

	BSTNode<K, V>* _pLeft;
	BSTNode<K, V>* _pRight;
	K _key;
	V _value;
};

template <typename K, typename V>
class BinarySearchTree
{
	typedef BSTNode<K, V> Node;
	
public:
	BinarySearchTree()
		:_pRoot(nullptr)
	{}

	bool Find_Nor(const K& key);	//非递归实现查找
	bool Find(const K& key)		//递归实现查找
	{
		return _Find(_pRoot, key);
	}

	void Insert_Nor(const K& key, const V& value);	//非递归实现插入
	void Insert(const K& key, const V& value)	//递归实现插入
	{
		_Insert(_pRoot, key, value);
	}
	void InOrder()
	{
		cout << "中序遍历：";
		_InOrder(_pRoot);
		cout << endl;
	}

	bool Remove_Nor(const K& key);
	bool Remove(const K& key)
	{
		return _Remove(_pRoot, key);
	}

private:
	bool _Find(Node* pRoot, const K& key);
	void _Insert(Node*& pRoot, const K& key, const V& value);
	void _InOrder(Node* pRoot);
	bool _Remove(Node* pRoot, const K& key);
private:
	Node* _pRoot;
};

template <typename K, typename V>
void BinarySearchTree<K, V>::_InOrder(Node* pRoot)
{
	if (pRoot)
	{
		_InOrder(pRoot->_pLeft);
		cout << pRoot->_key << " ";
		_InOrder(pRoot->_pRight);
	}
}

template <typename K, typename V>
bool BinarySearchTree<K, V>::Find_Nor(const K& key)
{
	Node* pCur = _pRoot;

	while (pCur)
	{
		if (key == pCur->_key)
			return true;
		else if (key < pCur->_key)
			pCur = pCur->_pLeft;
		else
			pCur = pCur->_pRight;
	}

	return false;
}

template <typename K, typename V>
bool BinarySearchTree<K, V>::_Find(Node* pRoot, const K& key)
{
	if (nullptr == pRoot)
		return false;

	if (key == pRoot->_key)
		return true;
	else if (key < pRoot->_key)
		return _Find(pRoot->_pLeft, key);
	else
		return _Find(pRoot->_pRight, key);
}

template <typename K, typename V>
void BinarySearchTree<K, V>::Insert_Nor(const K& key, const V& value)
{
	if (nullptr == _pRoot)
	{
		_pRoot = new Node(key, value);
		return ;
	}

	Node* pCur = _pRoot;
	Node* pParent = nullptr;
	while (pCur)
	{
		pParent = pCur;
		if (key == pCur->_key)
			return;
		else if (key < pCur->_key)
			pCur = pCur->_pLeft;
		else
			pCur = pCur->_pRight;
	}
	
	if (key < pParent->_key)
		pParent->_pLeft = new Node(key, value);
	else
		pParent->_pRight = new Node(key, value);
}

template <typename K, typename V>
void BinarySearchTree<K, V>::_Insert(Node*& pRoot, const K& key, const V& value)
{
	if (nullptr == pRoot)
	{
		pRoot = new Node(key, value);//空树时，创造节点
		return;
	}
	
	if (key == pRoot->_key)
		return;
	else if (key < pRoot->_key)
		_Insert(pRoot->_pLeft, key, value);
	else
		_Insert(pRoot->_pRight, key, value);
}

template <typename K, typename V>
bool BinarySearchTree<K, V>::Remove_Nor(const K& key)
{
	
}

#endif //_BST_H_
