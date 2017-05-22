#pragma once

#ifndef _AVL_H_
#define _AVL_H_

template <typename K, typename V>
struct AVLTreeNode
{
	AVLTreeNode(const K& key, const V& value)
		:_pParent(nullptr)
		,_pRight(nullptr)
		,_pLeft(nullptr)
		,_key(key)
		,_value(value)
		,_bf(0)//平衡因子默认为0(左子树高度 - 右子树高度)
	{}
	AVLTreeNode<K, V>* _pParent;
	AVLTreeNode<K, V>* _pRight;
	AVLTreeNode<K, V>* _pLeft;
	K _key;
	V _value;
	int _bf;//平衡因子
};

template <typename K, typename V>
class AVLTree
{
	typedef AVLTreeNode<K, V> Node;
public:
	AVLTree()
		:_pRoot(nullptr)
	{}

	bool Insert(const K& key, const V& value);

	//中序遍历
	void InOrder()
	{
		cout << "InOrder:";
		_InOrder(_pRoot);
		cout << endl;
	}
	//判断树是否是平衡树
	bool IsBalanceTree()
	{
		return _IsBalanceTree(_pRoot);
	}
private:
	//判断树是否是平衡树
	bool _IsBalanceTree(Node* pRoot);
	//获取树的高度
	size_t _Height(Node* pRoot);
	//中序遍历
	void _InOrder(Node* pRoot)
	{
		if (pRoot)
		{
			_InOrder(pRoot->_pLeft);
			cout << pRoot->_key << " ";
			_InOrder(pRoot->_pRight);
		}
	}
	//左单旋
	void _RotateL(Node* pParent);
	//右单旋
	void _RotateR(Node* pParent);
	//先右后左旋转
	void _RotateRL(Node* pParent);
	//先左后右旋转
	void _RotateLR(Node* pParent);

private:
	Node* _pRoot;
};


template <typename K, typename V>
bool AVLTree<K, V>::Insert(const K& key, const V& value)
{
	/*
	思路：
	1，空树
	2，非空树：插入到对应位置，并修改双亲的平衡因子。从插入的节点往上到根结点，判断是否有不满足AVL树性质的节点存在，并调整
	*/

	if (nullptr == _pRoot)
	{
		_pRoot = new Node(key, value);
		return true;
	}

	Node* pCur = _pRoot;//插入节点的位置
	Node* pParent = nullptr;//插入节点的双亲

	//找到节点应该插入的位置
	while (pCur)
	{
		if (key == pCur->_key)//存在相同节点，插入失败，返回false
		{
			return false;
		}
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

	//插入新节点
	Node* pNewNode = new Node(key, value);
	if (key < pParent->_key)//插在左边
		pParent->_pLeft = pNewNode;
	else  //插在右边
		pParent->_pRight = pNewNode;
	pNewNode->_pParent = pParent;
	pCur = pNewNode;

	while (pParent)//当往上循环到根节点时，退出循环
	{
		if (1 == pParent->_bf)
		{
			if (pParent->_pLeft == pCur)
			{
				++pParent->_bf;//此时pParent->_bf = 2（左边较高）,需要进行旋转
				// ..............
				Node* subL = pCur;
				if (1 == subL->_bf)//subL左边高 ，右单旋的情况
				{
					_RotateR(pParent);
				}
				else //-1 == subL->_bf,（没有0 == subL->_bf的可能） subL右边较高, 左右双旋的情况
				{
					_RotateLR(pParent);
				}
			}
			else
			{
				--pParent->_bf;//此时pParent->_bf = 0;没有添加一层，直接退出
				break;
			}
		}
		else if (-1 == pParent->_bf)
		{
			if (pParent->_pLeft == pCur)
			{
				++pParent->_bf;//此时pParent->_bf = 0;没有添加一层，直接退出
				break;
			}
			else
			{
				--pParent->_bf;//此时pParent->_bf = -2（右边较高）,需要进行旋转
				//........
				Node* subR = pCur;

				if (1 == subR->_bf)//subL左边较高， 左单旋的情况
				{
					_RotateL(pParent);
				}
				else // -1 == subR->_bf. subL右边较高（没有0 == subL->_bf的可能）， 左右单旋的情况
				{
					_RotateLR(pParent);
				}
			}
		}
		else //(0 == pParent->_bf)
		{
			if (pParent->_pLeft == pCur)
				++pParent->_bf;//此时pParent->_bf = 1
			else
				--pParent->_bf;//此时pParent->_bf = -1

			//由当前节点往根结点回溯
			pCur = pParent;
			pParent = pParent->_pParent;
		}
	}

	return true;
}

//左单旋
template <typename K, typename V>
void AVLTree<K, V>::_RotateL(Node* pParent)
{
	Node* subR = pParent->_pLeft;
	Node* subRL = subR->_pLeft;

	Node* pGrandParent = pParent->_pParent;//查看pParent是否是根结点

	pParent->_pRight = subRL;
	subRL->_pParent = pParent;

	subR->_pLeft = pParent;
	pParent->_pParent = subR;

	if (pGrandParent)//如果pParent存在双亲结点（即不是根结点）
	{	//将pParent的双亲结点重新指向subR
		if (pParent == pGrandParent->_pLeft)
			pParent->_pLeft = subR;
		else
			pParent->_pRight = subR;
	}	
	//subR的双亲指向pParent的双亲
	subR->_pParent = pGrandParent;

	//单旋转之后，pParent和subR的平衡因子置为0
	pParent->_bf = 0;
	subR->_bf = 0;
}

//右单旋
template <typename K, typename V>
void AVLTree<K, V>::_RotateR(Node* pParent)
{
	Node* subL = pParent->_pLeft;
	Node* subLR = subL->_pRight;

	Node* pGrandParent = pParent->_pParent;//查看pParent是否是根结点

	pParent->_pLeft = subLR;
	subLR->_pParent = pParent;

	subL->_pRight = pParent;
	pParent->_pParent = subL;

	if (pGrandParent)//如果pParent存在双亲结点（即不是根结点）
	{	//将pParent的双亲结点重新指向subL
		if (pParent == pGrandParent->_pLeft)
			pParent->_pLeft = subL;
		else
			pParent->_pRight = subL;
	}
	//subR的双亲指向pParent的双亲
	subL->_pParent = pGrandParent;

	//单旋转之后，pParent和subR的平衡因子置为0
	pParent->_bf = 0;
	subL->_bf = 0;
}

//先右后左旋转
template <typename K, typename V>
void AVLTree<K, V>::_RotateRL(Node* pParent)
{
	_RotateR(pParent->_pRight);
	_RotateL(pParent);
}

//先左后右旋转
template <typename K, typename V>
void AVLTree<K, V>::_RotateLR(Node* pParent)
{
	_RotateR(pParent->_pRight);
	_RotateL(pParent);
}

#endif //_AVL_H_