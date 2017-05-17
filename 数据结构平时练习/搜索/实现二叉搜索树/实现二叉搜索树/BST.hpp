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
		if (key == pCur->_key)
			break;
		else if (key < pCur->_key)
		{
			pParent = pCur;
			pCur = pCur->_pLeft;
		}
		else
		{
			pParent = pCur;
			pCur = pCur->_pRight;
		}
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
	//空树
	if (nullptr == _pRoot)
		return false;
	
	//只有一个根结点（不需使用双亲结点）
	if ((nullptr == _pRoot->_pLeft) && (nullptr == _pRoot->_pRight))
	{
		if (key == _pRoot->_key)//找到
		{
			delete _pRoot;
			_pRoot = nullptr;
			return true;
		}
		else//未找到
			return false;
	}

	//存在多个节点（需要使用双亲结点：必须双亲结点自己改变其左右孩子指向，pCur无法改变，最多删除自己变为空，双亲还是指向pCur原来位置）
	//1，未找到。
	//2，找到（1）没有左右子树（2）只有左子树（3）只有右子树（4）存在左右子树
	Node* pCur = _pRoot;//寻找值为key的节点
	Node* pParent = nullptr;//pCur的双亲节点
	while (pCur)
	{
		if (key == pCur->_key)
			break;
		else if (key < pCur->_key)
		{
			pParent = pCur;
			pCur = pCur->_pLeft;
		}
		else 
		{
			pParent = pCur;
			pCur = pCur->_pRight;
		}
	}

	if (nullptr == pCur)
		return false;//未找到

	if ((nullptr == pCur->_pLeft) && (nullptr == pCur->_pRight))	//是一个叶子结点
	{	//无需考虑，该结点是根结点的情况，前面已经考虑只有一个节点的情况了
		if (pParent->_pLeft == pCur)
			pParent->_pLeft = nullptr;
		else
			pParent->_pRight = nullptr;
	}
	else if (nullptr == pCur->_pRight)   //只有左孩子
	{	//1,pCur是根结点2，pCur不是根结点
		if (_pRoot == pCur)   //pCur是根节点
			_pRoot = pCur->_pLeft;//左孩子作为新根
		else   //pCur不是根结点,将其双亲结点指向它的左子树
		{
			if (pParent->_pLeft == pCur)//pCur是pParent的左子树
				pParent->_pLeft = pCur->_pLeft;
			else
				pParent->_pRight = pCur->_pLeft;//pCur是pParent的右子树
		}
	}
	else if (nullptr == pCur->_pLeft)	//只有右孩子
	{	//1,pCur是根结点2，pCur不是根结点
		if (_pRoot == pCur)   //pCur是根节点
			_pRoot = pCur->_pRight;//右孩子作为新根
		else   //pCur不是根结点,将其双亲结点指向它的左子树
		{
			if (pParent->_pLeft == pCur)//pCur是pParent的左子树
				pParent->_pLeft = pCur->_pRight;
			else
				pParent->_pLeft = pCur->_pRight;//pCur是pParent的右子树
		}
	}
	else    //存在左右子树（根结点大于左子树中全部节点，小于右子树中全部节点，可以将左子树中最大结点或右子树中最小节点代替，然后删除子树中的那个结点）
	{
		//找到右子树中最小的节点（右子树中最左边的叶子结点）
		pCur = pCur->_pRight;
		while (pCur->_pLeft)
			pCur = pCur->_pLeft;

		std::swap(pCur->_key, _pRoot->_key);
		std::swap(pCur->_value, _pRoot->_value);
	}

	delete pCur;
	pCur = nullptr;

	return true;
}

#endif //_BST_H_
