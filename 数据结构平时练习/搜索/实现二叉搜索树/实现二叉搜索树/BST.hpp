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

	bool Find_Nor(const K& key);	//�ǵݹ�ʵ�ֲ���
	bool Find(const K& key)		//�ݹ�ʵ�ֲ���
	{
		return _Find(_pRoot, key);
	}

	void Insert_Nor(const K& key, const V& value);	//�ǵݹ�ʵ�ֲ���
	void Insert(const K& key, const V& value)	//�ݹ�ʵ�ֲ���
	{
		_Insert(_pRoot, key, value);
	}
	void InOrder()
	{
		cout << "���������";
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
	bool _Remove(Node*& pRoot, const K& key);
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
		pRoot = new Node(key, value);//����ʱ������ڵ�
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
			return true;
		}
		else//δ�ҵ�
			return false;
	}

	//���ڶ���ڵ㣨��Ҫʹ��˫�׽�㣺����˫�׽���Լ��ı������Һ���ָ��pCur����ʱ������ֻ�ܸı��������ݺ��ͷ�������ָ�ڴ档�޷��ı䣬���Զ���ĵ�ַ�����ɾ���Լ���Ϊ�գ�˫�׻���ָ��pCurԭ��λ�ã�
	//1��δ�ҵ���
	//2���ҵ���1��û������������2��ֻ����������3��ֻ����������4��������������
	Node* pCur = _pRoot;//Ѱ��ֵΪkey�Ľڵ�
	Node* pParent = nullptr;//pCur��˫�׽ڵ�
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
		return false;//δ�ҵ�

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
			_pRoot = pCur->_pRight;//�Һ�����Ϊ�¸�
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

	return true;
}

template <typename K, typename V>
bool BinarySearchTree<K, V>::_Remove(Node*& pRoot, const K& key)
{
	//����
	if (nullptr == pRoot)
		return false;

	// ֻʣһ�����
	if ((nullptr == pRoot->_pLeft) && (nullptr == pRoot->_pRight))
		if (key == pRoot->_key)
		{
			delete pRoot;
			pRoot = nullptr;
			return true;
		}
		else
			return false;

	//����ڵ�
	if (key < pRoot->_key)
		return _Remove(pRoot->_pLeft, key);
	else if (key > pRoot->_key)
		return _Remove(pRoot->_pRight, key);
	else //key == pRoot->_key
	{
		Node* pCur = pRoot;//ָ����Ҫ��ɾ���Ľڵ�
		if (nullptr == pRoot->_pRight)//����ڵ㣬�ý��ֻ��������
		{
			pRoot = pRoot->_pLeft;
		}
		else if (nullptr == pRoot->_pLeft)//����ڵ㣬�ý��ֻ��������
		{
			pRoot = pRoot->_pRight;
		}
		else	//����ڵ㣬�ý�㺬����������
		{
			//�ҵ�����������С�Ľڵ㣨λ���������е������Ҷ�ӽڵ㣩
			Node* pParent = pCur;//ָ����Ҫɾ���ڵ��˫��
			pCur = pCur->_pRight;
			while (pCur->_pLeft)
			{
				pParent = pCur;
				pCur = pCur->_pLeft;
			}
			//�������ݣ�֮��ɾ���ڵ�
			std::swap(pRoot->_key, pCur->_key);
			std::swap(pRoot->_value, pCur->_value);

			if (pParent->_pLeft == pCur)
				pParent->_pLeft = nullptr;
			else
				pParent->_pRight = nullptr;
		}
		delete pCur;
		pCur = nullptr;
		return true;	
	}
}

#endif //_BST_H_