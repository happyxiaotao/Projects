#pragma once

#ifndef _BST_H_
#define _BST_H_

#include <iostream>
#include <assert.h>
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

//��ӵ�������û�п�������Ϊ�յ����
template <typename K, typename V, typename Ref, typename Ptr>
class Iterator
{
	
	typedef BSTNode<K, V> Node;
	typedef Iterator<K, V, Ref, Ptr> Self;
	typedef Ref value_Ref;
	typedef Ptr value_Ptr;

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

	Self& operator++()//ǰ��++
	{
		assert(_pNode);
		Increment(_pNode);
		return *this;
	}
	Self operator++(int)//����++
	{
		assert(_pNode);
		Self temp(*this);
		Increment(_pNode);
		return temp;
	}
	Self& operator--()//ǰ��--
	{
		assert(_pNode);
		Decrement(_pNode);
		return *this;
	}
	Self operator--(int)//����--
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
	void Increment(Node* pNode)//�ҽϴ�Ľڵ�,��ʱ������pNode
	{
		if (pNode->_pRight)//����������,��������������С�ĵ�
		{
			pNode = pNode->_pRight;
			while (pNode->_pLeft)
				pNode = pNode->_pLeft;
		}
		else//������������
		{
			Node* pParent = pNode->_pParent;
			while (pParent->_pRight == pNode)
			{
				pNode = pParent;
				pParent = pNode->_pParent;
			}

			if (pNode->_pRight != pParent)//���������ͷ��������£� ֱ��ִ�к����Ч���
				pNode = pParent;
		}
		_pNode = pNode;
	}
	void Decrement(Node* pNode)//�ҽ�С�Ľڵ�
	{
		if (pNode->_pLeft)//����������,�������������Ľڵ�
		{
			pNode = pNode->_pLeft;
			while (pNode->_pRight)
				pNode = pNode->_pRight;
		}
		else	//������������
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
	typedef Iterator<K, V, K&, K*> iterator;//��������Ҫ���У�ʹ��������
private:
		typedef BSTNode<K, V> Node;
public:
	BinarySearchTree()
	{
		_pHead = new Node();
	}

	Node* GetRoot()
	{
		return _pHead->_pParent;
	}
	bool Find_Nor(const K& key);	//�ǵݹ�ʵ�ֲ���
	bool Find(const K& key)		//�ݹ�ʵ�ֲ���
	{
		return _Find(GetRoot(), key);
	}

	void Insert_Nor(const K& key, const V& value);	//�ǵݹ�ʵ�ֲ���

	bool Remove_Nor(const K& key);//�ǵݹ�ʵ��ɾ��

	void InOrder()
	{
		cout << "���������";
		_InOrder(GetRoot());
		cout << endl;
	}

public:	//����������
	iterator Begin()
	{
		return iterator(_pHead->_pLeft);
	}
	iterator End()
	{
		return iterator(_pHead);
	}
public://������������ת��Ϊ����˫������
	Node* ToList()
	{
		//������ĳһ���ĺ�̣�����������иýڵ�������ʵ���һ�ڵ㣬���ý���������ָ��������ʵ���һ�ڵ㼴��
		Node* pHead = GetRoot();//�����ͷ���
		Node* pPrev = nullptr;//������������е�pHead��ǰһ���ڵ�
		
		_ToList(pHead, pPrev);//ע��pPrev����������

		if (nullptr != pHead)//ע�⣬pHead�����ǿյ����
		{
			while (pHead->_pLeft)//�ҵ������ͷ��㣨��С�Ľڵ㣩����_ToList�����У�ֻ�ı�����������ָ��δ�ı���������ָ��
				pHead = pHead->_pLeft;
		}
		return pHead; //��������ͷ���
	}

private:
	bool _Find(Node* pRoot, const K& key);
	void _InOrder(Node* pRoot);
	Node* FindMin();//��ȡ���ֵ�ڵ�
	Node* FindMax();//��ȡ��Сֵ�ڵ�
	void _ToList(Node* pRoot, Node*& pPrev);//ע��pPrev����������
private:
	Node* _pHead;//ͷ��㣨�൱�ڵ�������End()ָ��Ľڵ㣬���Һ��ӷֱ�ָ��������С����㣬˫�׽�������ĸ���㣩
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
				return ;//�������
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

	//����
	if (nullptr == _pRoot)
		return false;

	//ֻ��һ������㣨����ʹ��˫�׽�㣩
	if ((nullptr == _pRoot->_pLeft) && (nullptr == _pRoot->_pRight))
	{
		if (key == _pRoot->_key)//�ҵ�
		{
			delete _pRoot;
			_pRoot = nullptr;

			_pHead->_pLeft = nullptr;
			_pHead->_pRight = nullptr;
			_pHead->_pParent = nullptr;

			return true;
		}
		else//δ�ҵ�
			return false;
	}

	//���ڶ���ڵ㣨��Ҫʹ��˫�׽�㣺����˫�׽���Լ��ı������Һ���ָ��pCur����ʱ������ֻ�ܸı��������ݺ��ͷ�������ָ�ڴ档�޷��ı䣬���Զ���ĵ�ַ�����ɾ���Լ���Ϊ�գ�˫�׻���ָ��pCurԭ��λ�ã�
	//1��δ�ҵ���
	//2���ҵ���1��û������������2��ֻ����������3��ֻ����������4��������������
	Node* pCur = _pRoot;//Ѱ��ֵΪkey�Ľڵ�
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

	if (nullptr == pCur)//δ�ҵ�
		return false;
	else
	{
		Node* pParent = pCur->_pParent;//pCur��˫�׽ڵ�
		if ((nullptr == pCur->_pLeft) && (nullptr == pCur->_pRight))	//��һ��Ҷ�ӽ��
		{	//���迼�ǣ��ý���Ǹ����������ǰ���Ѿ�����ֻ��һ���ڵ�������
			if (pParent->_pLeft == pCur)
				pParent->_pLeft = nullptr;
			else
				pParent->_pRight = nullptr;
		}
		else if (nullptr == pCur->_pRight)   //ֻ������
		{	//1,pCur�Ǹ����2��pCur���Ǹ����
			if (_pRoot == pCur)   //pCur�Ǹ��ڵ�
				_pRoot = pCur->_pLeft;//������Ϊ�¸�
			else   //pCur���Ǹ����,����˫�׽��ָ������������
			{
				if (pParent->_pLeft == pCur)//pCur��pParent��������
					pParent->_pLeft = pCur->_pLeft;
				else
					pParent->_pRight = pCur->_pLeft;//pCur��pParent��������
			}
		}
		else if (nullptr == pCur->_pLeft)	//ֻ���Һ���
		{	//1,pCur�Ǹ����2��pCur���Ǹ����
			if (_pRoot == pCur)   //pCur�Ǹ��ڵ�
			{
				_pRoot = pCur->_pRight;//�Һ�����Ϊ�¸�
				_pHead->_pParent = _pRoot;
				_pRoot->_pParent = _pHead;
			}
			else   //pCur���Ǹ����,����˫�׽��ָ������������
			{
				if (pParent->_pLeft == pCur)//pCur��pParent��������
					pParent->_pLeft = pCur->_pRight;
				else
					pParent->_pLeft = pCur->_pRight;//pCur��pParent��������
			}
		}
		else    //������������������������������ȫ���ڵ㣬С����������ȫ���ڵ㣬���Խ�������������������������С�ڵ���棬Ȼ��ɾ�������е��Ǹ���㣩
		{
			//�ҵ�����������С�Ľڵ㣨������������ߵ�Ҷ�ӽ�㣩
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

template <typename K, typename V>
void BinarySearchTree<K, V>::_ToList(Node* pRoot, Node*& pPrev)//ע��pPrev����������
{//������ĳһ���ĺ�̣�����������иýڵ�������ʵ���һ�ڵ㣬���ý���������ָ��������ʵ���һ�ڵ㼴��
	if (nullptr == pRoot)
		return;

	_ToList(pRoot->_pLeft, pPrev);//��δ��ʼ���ʣ�ֻ����Ѱ�����е�һ���ڵ㣬����pPrev����

	if (nullptr != pPrev)//pPrev��nullptr˵����ʱ���ڷ��ʵ�һ���ڵ㣨�������ͷ��㣬û��ǰ����
		pPrev->_pRight = pRoot;

	pPrev = pRoot;//����pPrev

	_ToList(pRoot->_pRight, pPrev);
}

#endif //_BST_H_