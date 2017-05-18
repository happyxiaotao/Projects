#pragma once

#ifndef _BST_H_
#define _BST_H_

#include <iostream>
using namespace std;

template <typename K, typename V>
struct BSTNode
{
	BSTNode(const K& key = K(), const V& value = V())
		:_pParent(nullptr)
		, _pLeft(nullptr)
		, _pRight(nullptr)
		, _key(key)
		, _value(value)
	{}

	BSTNode<K, V>* _pParent;
	BSTNode<K, V>* _pLeft;
	BSTNode<K, V>* _pRight;
	K _key;
	V _value;
};

template <typename K, typename V, typename Ref, typename Ptr>
class Iterator
{
	typedef BSTNode<K, V> Node;
	typedef Iterator<K, V, Ref, Ptr> Self;

public:
	Iterator()
		:_pNode(nullptr)
	{}
	Iterator(Node* pNode)
		:_pNode(pNode)
	{}
	Iterator(const Self& it)
	{
		_pNode = it._pNode;
	}
	Self& operator=(const Self& it)
	{
		if (this != &it)
		{
			_pNode = it._pNode;
		}
		return *this;
	}
public:

	Self& operator++()//前置++
	{
		Increment(_pNode);
		return *this;
	}
	Self operator++(int)//后置++
	{
		Self temp(*this);
		Increment(_pNode);
		return temp;
	}
	Self& operator--()//前置--
	{
		Decrement(_pNode);
		return *this;
	}
	Self operator--(int)//后置--
	{
		Self temp(*this);
		Decrement(_pNode);
		return temp;
	}

	bool operator == (const Self& it)
	{
		return _pNode == it._pNode;
	}
	bool operator != (const Self& it)
	{
		return !(*this == it);
	}

	Node& operator *()
	{
		return (*_pNode);
	}
	Node* operator -> ()
	{
		return _pNode;
	}

private:
	void Increment(Node* pNode)//找较大的节点,暂时保存在pNode
	{
		if (pNode->_pRight)//右子树存在,，找右子树中最小的点
		{
			pNode = pNode->_pRight;
			while (pNode->_pLeft)
				pNode = pNode->_pLeft;
		}
		else//右子树不存在
		{
			Node* pParent = pNode->_pParent;
			while (pParent->_pRight == pNode)
			{
				pNode = pParent;
				pParent = pNode->_pParent;
			}

			if (pNode->_pRight != pParent)//避免根结点和头结点的情况下， 直接执行后的无效结果
				pNode = pParent;
		}
		_pNode = pNode;
	}
	void Decrement(Node* pNode)//找较小的节点
	{
		if (pNode->_pLeft)//左子树存在,找左子树中最大的节点
		{
			pNode = pNode->_pLeft;
			while (pNode->_pRight)
				pNode = pNode->_pRight;
		}
		else	//左子树不存在
		{
			Node* pParent = pNode->_pParent;
			while (pParent->_pLeft == pNode)
			{
				pNode = pParent;
				pParent = pNode->_pParent;
			}

			if (pNode->_pLeft != pParent)
				pNode = pParent;
		}

		_pNode = pNode;
	}
private:
	Node* _pNode;
};

template <typename K, typename V>
class BinarySearchTree
{
public:
	typedef BSTNode<K, V> Node;
	typedef Iterator<K, V, K&, K*> iterator;
public:
	BinarySearchTree()
	{
		_pHead = new Node();
	}

	Node* GetRoot()
	{
		return _pHead->_pParent;
	}
	bool Find_Nor(const K& key);	//非递归实现查找
	bool Find(const K& key)		//递归实现查找
	{
		return _Find(GetRoot(), key);
	}

	void Insert_Nor(const K& key, const V& value);	//非递归实现插入

	bool Remove_Nor(const K& key);//非递归实现删除

	void InOrder()
	{
		cout << "中序遍历：";
		_InOrder(GetRoot());
		cout << endl;
	}

	iterator Begin()
	{
		return iterator(_pHead->_pLeft);
	}
	iterator End()
	{
		return iterator(_pHead);
	}

private:
	bool _Find(Node* pRoot, const K& key);
	void _InOrder(Node* pRoot);
	Node* FindMin();
	Node* FindMax();
private:
	Node* _pHead;
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
	Node* _pRoot = GetRoot();
	if (nullptr == _pRoot)
	{
		_pRoot = new Node(key, value);
		_pRoot->_pParent = _pHead;
		_pHead->_pParent = _pRoot;
	}
	else
	{
		Node* pCur = GetRoot();
		Node* pParent = nullptr;
		while (pCur)
		{
			if (key == pCur->_key)
				return ;//无需插入
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
		{
			pParent->_pLeft = new Node(key, value);
			pParent->_pLeft->_pParent = pParent;
		}
		else
		{
			pParent->_pRight = new Node(key, value);
			pParent->_pRight->_pParent = pParent;
		}
	}

	_pHead->_pLeft = FindMin();
	_pHead->_pRight = FindMax();
}

template <typename K, typename V>
bool BinarySearchTree<K, V>::Remove_Nor(const K& key)
{

	Node* _pRoot = GetRoot();

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

			_pHead->_pLeft = nullptr;
			_pHead->_pRight = nullptr;
			_pHead->_pParent = nullptr;

			return true;
		}
		else//未找到
			return false;
	}

	//存在多个节点（需要使用双亲结点：必须双亲结点自己改变其左右孩子指向，pCur是临时变量，只能改变自身内容和释放内容所指内存。无法改变，所以对象的地址，最多删除自己变为空，双亲还是指向pCur原来位置）
	//1，未找到。
	//2，找到（1）没有左右子树（2）只有左子树（3）只有右子树（4）存在左右子树
	Node* pCur = _pRoot;//寻找值为key的节点
	while (pCur)
	{
		if (key == pCur->_key)
			break;
		else if (key < pCur->_key)
		{
			pCur = pCur->_pLeft;
		}
		else
		{
			pCur = pCur->_pRight;
		}
	}

	if (nullptr == pCur)//未找到
		return false;
	else
	{
		Node* pParent = pCur->_pParent;//pCur的双亲节点
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
			{
				_pRoot = pCur->_pRight;//右孩子作为新根
				_pHead->_pParent = _pRoot;
				_pRoot->_pParent = _pHead;
			}
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

		_pHead->_pLeft = nullptr;
		_pHead->_pRight = nullptr;
	}

	return true;
}

template <typename K, typename V>
BSTNode<K, V>* BinarySearchTree<K, V>::FindMin()
{
	Node* pMin = nullptr;

	if (pMin = GetRoot())
	{
		while (pMin->_pLeft)
			pMin = pMin->_pLeft;
	}

	return pMin;
}

template <typename K, typename V>
BSTNode<K, V>* BinarySearchTree<K, V>::FindMax()
{
	Node* pMax = nullptr;

	if (pMax = GetRoot())
	{
		while (pMax->_pRight)
			pMax = pMax->_pRight;
	}

	return pMax;
}

#endif //_BST_H_