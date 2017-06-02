#pragma once

#ifndef _RBTREE_H_
#define _RBTREE_H_

/*
拓展，给红黑树添加迭代器
*/

#include <iostream>
#include <assert.h>
using namespace std;

/*
红黑树性质：
1，每个节点不是红色，就是黑色
2，根结点只能是黑色
3，如果当前节点时红色，那么它的两个孩子节点只能是黑色（即没有连续的红色）
4，对于每个节点，从该结点到其后代叶子结点的简单路径上，均包含相同数目的黑色节点（每条路径上黑色节点的数量相等）
隐藏性质：（空结点可以看做是黑色的）
*/

enum COLOR { RED, BLACK };

template <typename K, typename V>
struct RBTreeNode
{
	RBTreeNode(const K& key = K(), const V& value = V(), COLOR color = RED)
		: _pParent(nullptr)
		, _pLeft(nullptr)
		, _pRight(nullptr)
		, _key(key)
		, _value(value)
		, _color(color)//节点默认是红色的，因为维护性质3比维护性质4方便
	{}

	RBTreeNode<K, V>* _pParent;
	RBTreeNode<K, V>* _pLeft;
	RBTreeNode<K, V>* _pRight;

	K _key;
	V _value;
	COLOR _color;
};


//迭代器
template <typename K, typename V, typename Ref, typename Ptr>
struct Iterator
{
	typedef RBTreeNode<K, V> Node;
	typedef Iterator<K, V, K&, K*> Self;
	typedef Ref value_Ref;
	typedef Ptr value_Ptr;

	//构造函数
	Iterator(Node* pNode = nullptr)
		:_pNode(pNode)
	{}

	//拷贝构造函数
	Iterator(const Self& it)
	{
		_pNode = it._pNode;
	}

	//赋值运算符重载函数
	Self& operator = (const Self& it)
	{
		if (this != &it)
			_pNode = it._pNode;
		return *this;
	}

	Self& operator++()//前置++
	{
		assert(_pNode);
		Increment(_pNode);
		return *this;
	}

	Self operator++(int)//后置++
	{
		assert(_pNode);
		Self temp(*this);
		Increment(_pNode);
		return temp;
	}

	Self& operator--()//前置--
	{
		assert(_pNode);
		Decrement(_pNode);
		return *this;
	}

	Self operator--(int)//后置--
	{
		assert(_pNode);
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

	value_Ref operator *()
	{
		assert(_pNode);
		return (_pNode->_key);
	}

	value_Ptr operator -> ()
	{
		assert(_pNode);
		return &(operator*());
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
class RBTree
{
public:
	typedef Iterator<K, V, K&, K*> iterator;//要设置公有的，外界才能访问

private:
	typedef RBTreeNode<K, V> Node;

public:
	RBTree()
	{
		_pHead =  new Node();//创建头结点
	}

public:

	iterator Begin()//不可以是引用
	{
		return iterator(_pHead->_pLeft);
	}

	iterator End()//不可是引用
	{
		return iterator(_pHead);
	}

	//插入操作
	bool Insert(const K& key, const V& value, COLOR color = RED);

	//中序遍历
	void InOrder()
	{
		cout << "中序遍历：" << endl;
		_InOrder(GetRoot());
		cout << endl;
	}

	//检查是否符合红黑树性质
	bool CheckRBTree();

private:
	//获取根结点
	Node* GetRoot()
	{
		return _pHead->_pParent;
	}

	//左单旋
	void _TotalL(Node* pParent);

	//右单旋
	void _TotalR(Node* pParent);

	//中序遍历
	void _InOrder(Node* pRoot);
	
	//找到最小的节点
	Node* _FindMin()
	{
		Node* pCur = GetRoot();
		
		if (pCur)
			while (pCur->_pLeft)
				pCur = pCur->_pLeft;
		
		return pCur;
	}
	
	//找到最大的节点
	Node* _FindMax()
	{
		Node* pCur = GetRoot();
		
		if (pCur)
			while (pCur->_pRight)
				pCur = pCur->_pRight;
			
		return pCur;
	}
	
	//检查是否符合红黑树性质
	//blackCount表示树中，每条最短路径上黑色个数，k表述当前到达该节点的路径上，黑色节点个数（不算本节点的黑色）
	bool _CheckRBTree(const Node* pRoot, const size_t blackCount, size_t k);

private:
	Node* _pHead;
};

//插入操作
template <typename K, typename V>
bool RBTree<K, V>::Insert(const K& key, const V& value, COLOR color)
{
	/*
	cur：表示插入的节点
	p：双亲结点
	g：祖父母节点
	u：叔叔节点

	五种情况：
	1，空树
	2，p->color = black，直接插入
	3, p->color = red, (u && u->color = red)，p、u颜色变为black，g颜色变为red
	4，p->color = red, (u = nullptr || u->color = black),cur,p,g在同一条直线，进行相应左/右单选处理（g作为参数），然后，原来p g颜色互换
	5，p->color = red, (u = nullptr || u->color = black),cur,p,g不在同一条直线，进行相应左/右单选（p作为参数），变为情况4处理
	*/

	Node* pRoot = GetRoot();
	//空树，情况一
	if (nullptr == pRoot)
	{
		pRoot = new Node(key, value, BLACK);//根指向新的节点，根节点是黑色的
		pRoot->_pParent = _pHead;
		
		//头结点与根结点的双亲互指
		_pHead->_pLeft = pRoot;
		_pHead->_pRight = pRoot;
		_pHead->_pParent = pRoot;

		return true;
	}

	//树不空，找到插入的位置

	Node* pCur = pRoot;//应该插入的位置 cur
	Node* pParent = nullptr;//插入节点的双亲节点 p

	//寻找插入位置
	while (pCur)
	{
		if (key == pCur->_key)
			return false;//节点已存在，插入失败
		else if (key < pCur->_key)//向pCur的左子树种寻找
		{
			pParent = pCur;//pParent在pCur变化前更新，不能喝下一语句顺序搞反了
			pCur = pCur->_pLeft;
		}
		else // key > pCur->_key 向pCur的右子树种寻找
		{
			pParent = pCur;
			pCur = pCur->_pRight;
		}
	}

	//先添加，在考虑调整情况（若接下来不满足循环中条件，则本次添加属于情况二）
	Node* pNewNode = new Node(key, value);	//创建新的节点
	pNewNode->_pParent = pParent;	//调整双亲指向
	if (key < pParent->_key)	//新节点应该插入到左边
		pParent->_pLeft = pNewNode;
	else						//新节点应该插入到右边
		pParent->_pRight = pNewNode;

	pCur = pNewNode;//记住，要随时更新指向，在下面循环中处理

	while ((pParent != _pHead) && (RED == pParent->_color))//pParent不是根结点 并且 颜色是红色
	{
		Node* pGrandParent = pParent->_pParent;//祖父母节点g

		if (pParent == pGrandParent->_pLeft)//p在g的左边
		{
			Node* pUncle = pGrandParent->_pRight;//cur的叔叔节点u

			if (pUncle && (RED == pUncle->_color)) //情况三，pUncle存在且颜色为红
			{	//p与u调整为BLACK，g调整为RED
				pParent->_color = BLACK;
				pUncle->_color = BLACK;
				pGrandParent->_color = RED;

				pCur = pGrandParent;//向上调整，为下次循环做准备
				pParent = pCur->_pParent;//向上调整，pParent指向新的根结点pCur的双亲
			}
			else //nullptr == pUncle || BLACK == pUncle->_color   pUncle不存在或者存在且颜色为黑
			{
				//由于情况5可以转换为情况4，所以将两种情况合并到一次循环中

				if (pCur == pParent->_pRight)//cur, p, g不在同一条直线上	//情况五
				{
					_TotalL(pParent);//左单旋 

									 //此时不用交换颜色，变为 情况四，在下面处理

					std::swap(pParent, pCur);//注意交换，pParent，pCur的内容，方便情况4处理
				}

				_TotalR(pGrandParent);//右单旋， cur，p都处于各自双亲的左子树（cur, p, g在同一条直线）//情况四

									  //p与g颜色互换
				pParent->_color = BLACK;
				pGrandParent->_color = RED;
				
				break;
				//调整完后，应该直接退出（当前树，已经满足红黑树性质，而该树意外的树本来就是满足红黑树性质，所以，直接退出，----调试半天）
				//pCur = pParent;//向上调整，为下次循环做准备，指向新的根结点
				//pParent = pCur->_pParent;//向上调整，pParent指向新的根结点pCur的双亲 
				//若添加上述代码,则有课能pParent的双亲结点颜色是red，继续进入循环，发生不可预料的意外
			}

		}
		else	//p在g的右边
		{
			Node* pUncle = pGrandParent->_pLeft;//cur的叔叔节点u

			if (pUncle && (RED == pUncle->_color)) //情况三
			{	//p与u调整为BLACK，g调整为RED
				pParent->_color = BLACK;
				pUncle->_color = BLACK;
				pGrandParent->_color = RED;

				pCur = pGrandParent;			//向上调整，为下次循环做准备
				pParent = pCur->_pParent;//向上调整，pParent指向新的根结点pCur的双亲
			}
			else //pUncle = nullptr || BLACK == pUncle->_color
			{
				//由于情况5可以转换为情况4，所以将两种情况合并到一次循环中

				// cur,p,g不在同一条直线上	//情况五
				if (pCur = pParent->_pLeft)
				{
					_TotalR(pParent); //右单旋
									  //此时不用交换颜色，变为 情况四，在下次循环中处理
					std::swap(pParent, pCur);////注意交换，pParent，pCur的内容，方便情况4处理
				}

				//cur，p都处于各自双亲的右子树（cur, p, g在同一条直线）//情况四
				_TotalL(pGrandParent);		//左单旋

											//p与g颜色互换
				pParent->_color = BLACK;
				pGrandParent->_color = RED;

				//退出原因，见上面 情况4解释
				break;
			}
		}
	}

	_pHead->_pParent->_color = BLACK;//不管怎么调整，根节点始终是黑色，而且黑色可以连续
	
	_pHead->_pLeft = _FindMin();
	_pHead->_pRight = _FindMax();
	
	return true;
}

//右单旋
template <typename K, typename V>
void RBTree<K, V>::_TotalR(Node* pParent)
{
	Node* pSubL = pParent->_pLeft;
	Node* pSubLR = pSubL->_pRight;

	pParent->_pLeft = pSubLR;
	pSubL->_pRight = pParent;

	if (pSubLR)
		pSubLR->_pParent = pParent;

	Node* pGrandParent = pParent->_pParent;
	pParent->_pParent = pSubL;
	pSubL->_pParent = pGrandParent;
	if (/*pGrandParent && */(pGrandParent != _pHead))//可以证明pGrandParent是一定存在的
	{
		if (pGrandParent->_pLeft == pParent)//注意，使用==，不要忘记写出=（调试半天）
			pGrandParent->_pLeft = pSubL;
		else
			pGrandParent->_pRight = pSubL;
	}
	else
		_pHead->_pParent = pSubL;

}

//左单旋
template <typename K, typename V>
void RBTree<K, V>::_TotalL(Node* pParent)
{
	Node* pSubR = pParent->_pRight;
	Node* pSubRL = pSubR->_pLeft;

	pParent->_pRight = pSubRL;
	pSubR->_pLeft = pParent;

	if (pSubRL)
		pSubRL->_pParent = pParent;

	Node* pGrandParent = pParent->_pParent;
	pParent->_pParent = pSubR;
	pSubR->_pParent = pGrandParent;
	if (/*pGrandParent && */(pGrandParent != _pHead))//可以证明pGrandParent是一定存在的
	{
		if (pGrandParent->_pLeft == pParent)//注意，使用==，不要忘记写出=
			pGrandParent->_pLeft = pSubR;
		else
			pGrandParent->_pRight = pSubR;
	}
	else
		_pHead->_pParent = pSubR;
}

//递归实现中序遍历
template <typename K, typename V>
void RBTree<K, V>::_InOrder(Node* pRoot)
{
	if (nullptr == pRoot)
		return;

	_InOrder(pRoot->_pLeft);

	cout << pRoot->_key << " ";

	_InOrder(pRoot->_pRight);
}

template <typename K, typename V>
bool RBTree<K, V>::CheckRBTree()
{
	Node* pRoot = GetRoot();
	//空树，满足红黑树性质
	if (nullptr == pRoot)
		return true;

	//根结点是红色的，违反性质2
	if (RED == pRoot->_color)
	{
		cout << "根结点是红色的，违反性质2" << endl;
		return false;
	}

	size_t blackCount = 0;//保存一条从根结点到叶子结点上黑色节点的个数
	Node* pCur = pRoot;
	while (pCur)
	{
		if (BLACK == pCur->_color)
			++blackCount;
		pCur = pCur->_pLeft;
	}
	//在下面递归函数中，检查性质3和性质4
	return _CheckRBTree(pRoot, blackCount, 0);
}

//判断是否满足红黑树性质3与性质4
//blackCount表示树中，每条最短路径上黑色个数，k表述当前到达该节点的路径上，黑色节点个数（不算本节点的黑色）
template <typename K, typename V>
bool RBTree<K, V>::_CheckRBTree(const Node* pRoot, size_t blackCount, size_t k)
{
	//注意：k是普通变量，不能用引用，因为递归中，每个节点中k都不一样，递归返回后，需要当前节点k值来重新计算，不能在别的树中，被改变

	if (nullptr == pRoot)//空树，符合红黑树所有性质
		return true;

	if (BLACK == pRoot->_color)//当前节点颜色是黑色
		++k;
	else			//当前节点是红色
	{
		if (RED == pRoot->_pParent->_color) //判断红色节点是否连续
		{
			cout << "有连续的红色节点，不满足性质3" << endl;
			return false;
		}
	}

	if ((nullptr == pRoot->_pLeft) && (nullptr == pRoot->_pRight))//叶子结点
	{
		if (blackCount == k)//判断当前路径上的黑色节点是否和别的路径上结点相等
			return true;
		else
		{
			cout << "红黑树每条最短路径上黑色节点个数不同，不满足性质4" << endl;
			return false;
		}
	}

	//处理非叶子结点的情况，其左右子树也必须满足红黑树性质
	return (_CheckRBTree(pRoot->_pLeft, blackCount, k) && _CheckRBTree(pRoot->_pRight, blackCount, k));
}


#endif //_RBTREE_H_

