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

				if (1 == subR->_bf)//subL左边较高
				{
					if (1 == subR->_pLeft->_bf)//插入节点是sub的左子节点的左子节点（右单旋）
						_RotateR(pParent);
					else    //插入节点是sub的左子节点的右子节点（右左单选）
						_RotateRL(pParent);
				}
				else // -1 == subR->_bf. subL右边较高（没有0 == subL->_bf的可能）
				{
					if (1 == subR->_pRight->_bf) //插入节点是sub的右子节点的左子节点（左右双选）
						_RotateLR(pParent);
					else //插入节点是sub的右子节点的右子节点（左单旋）
						_RotateL(pParent);
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
	if (subRL)//如果subRL存在
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
	if(subLR)//如果subLR存在
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
	/*可以使用k1,k2,k3标记。参考《数据结构与算法分析C++语言描述版》*/
	Node* subR = pParent->_pRight;
	Node* subRL = subR->_pLeft;

	int flag = 0;//记录pNewNode与subRL的关系

	if (0 == subRL->_bf)//subRL是刚插入的节点pNewNode
		flag = 0;
	else if (1 == subRL->_bf)//pNewNode在subRL的左子树中
		flag = 1;
	else //-1 == subRL->_bf pNewNode在subRL的右子树上
		flag = -1;

	_RotateL(pParent->_pRight);
	_RotateR(pParent);

	//更新平衡因子（不需要考虑subRL，因为在单旋转之后，其平衡因子为0，不需改变）
	if (0 == flag)//subRL是刚插入的节点pNewNode
	{
		subR->_bf = 0;
		pParent->_bf = 0;
	}
	else if (1 == flag)//pNewNode在subRL的左子树中
	{
		subR->_bf = -1;
		pParent->_bf = 0;
	}
	else //-1 == flag pNewNode在subRL的右子树上
	{
		subR->_bf = 0;
		pParent->_bf = 1;
	}
}

//先左后右旋转
template <typename K, typename V>
void AVLTree<K, V>::_RotateLR(Node* pParent)
{
	/*可以使用k1,k2,k3标记。参考《数据结构与算法分析C++语言描述版》*/
	Node* subL = pParent->_pLeft;
	Node* subLR = subL->_pRight;

	int flag = 0;//记录pNewNode与subLR的关系

	if (0 == subLR->_bf)//subLR是刚插入的节点pNewNode
		flag = 0;
	else if (1 == subLR->_bf)//pNewNode在subLR的左子树中
		flag = 1;
	else //-1 == subLR->_bf pNewNode在subLR的右子树上
		flag = -1;


	_RotateR(subL);
	_RotateL(pParent);


	//更新平衡因子（不需要考虑subLR，因为在单旋转之后，其平衡因子为0，不需改变）
	if (0 == flag)//subLR是刚插入的节点pNewNode
	{
		subL->_bf = 0;
		pParent->_bf = 0;
	}
	else if (1 == flag)//pNewNode在subLR的左子树中
	{
		subL->_bf = 0;
		pParent->_bf = -1;
	}
	else //-1 == flag pNewNode在subLR的右子树上
	{
		subL->_bf = 1;
		pParent->_bf = 0;
	}
}


//判断树是否是平衡树
template <typename K, typename V>
bool AVLTree<K, V>::_IsBalanceTree(Node* pRoot)
{
	if (nullptr == pRoot)//空结点，是平衡的
		return true;

	size_t leftHeight = _Height(pRoot->_pLeft);
	size_t rightHeight = _Height(pRoot->_pRight);

	if (((leftHeight - rightHeight) != pRoot->_bf) || (abs(pRoot->_bf) > 2))
		return false;

	return (_IsBalanceTree(pRoot->_pLeft) && _IsBalanceTree(pRoot->_pRight));
}

//获取树的高度
template <typename K, typename V>
size_t AVLTree<K, V>::_Height(Node* pRoot)
{
	if (nullptr == pRoot)//空树
		return 0;

	if ((nullptr == pRoot->_pLeft) && (nullptr == pRoot->_pRight))//叶子结点
		return 1;

	size_t leftHeight = _Height(pRoot->_pLeft);//左子树高度
	size_t rightHeight = _Height(pRoot->_pRight);//右子树高度

	return leftHeight > rightHeight ? leftHeight + 1 : rightHeight + 1;//返回左右子树中的最大值+1
}

#endif //_AVL_H_