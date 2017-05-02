/*
���������������ԣ��������õݹ����Ϻõ�ʵ��������ع���
*/
#pragma once
#ifndef _BINARYTREE_H_
#define _BINARYTREE_H_

#include <iostream>
#include <queue>
#include <stack>
using namespace std;

template <typename T>
struct BinaryTreeNode
{
	BinaryTreeNode(const T& data)
		:m_data(data)
		, m_pLeft(NULL)
		, m_pRight(NULL)
	{}
	T m_data;
	BinaryTreeNode<T>* m_pLeft;//����
	BinaryTreeNode<T>* m_pRight;//�Һ���
};

template <typename T>
class BinaryTree//����Ա������ʵ�ֽ��м򵥵ķ�װ���û�ֻ����ʾ���ù����ӿ�
{
	typedef BinaryTreeNode<T> Node;
public:
	BinaryTree()//�޲ι��캯��
		:m_pRoot(NULL)
	{}
	BinaryTree(const T array[], size_t size, const T& invalid)//���ι��캯��
	{
		size_t index = 0;
		_CreateTree(m_pRoot, array, size, index, invalid);
	}
	BinaryTree(const BinaryTree<T>& t)//�������캯��
	{
		m_pRoot = _CopyBinaryTree(t.m_pRoot);
	}
	BinaryTree<T>& operator=(const BinaryTree<T>& t)//��ֵ��������س�Ա����
	{
		_Destroy(m_pRoot);
		m_pRoot = _CopyBinaryTree(t.m_pRoot);
		return *this;
	}
	~BinaryTree()//��������
	{
		_Destroy(m_pRoot);
	}
	void PreOrder()//ǰ�����
	{
		cout << "ǰ�������";
		_PreOrder_2(m_pRoot);
		cout << endl;
	}
	void InOrder()//�������
	{
		cout << "�������";
		_InOrder_2(m_pRoot);
		cout << endl;
	}
	void PostOrder()//�������
	{
		cout << "�������";
		_PostOrder(m_pRoot);
		cout << endl;
	}
	void LevelOrder()//�������
	{
		cout << "�������";
		_LevelOrder(m_pRoot);
		cout << endl;
	}

private:
	void _CreateTree(Node*& pRoot, const T array[], size_t size, size_t& index, const T& invalid);//������
	Node* _CopyBinaryTree(Node* pRoot);//������
	void _Destroy(Node*& pRoot);//�����
	void _PreOrder_1(Node* pRoot);//�ݹ�ʵ�֣��������
	void _PreOrder_2(Node* pRoot);//�ǵݹ�ʵ�֣��������
	void _InOrder_1(Node* pRoot);//�ݹ�ʵ�֣��������
	void _InOrder_2(Node* pRoot);//�ѵݹ�ʵ�֣��������
	void _PostOrder(Node* pRoot);//�������
	void _LevelOrder(Node* pRoot);//�������

private:
	BinaryTreeNode<T>* m_pRoot;
};

template <typename T>
void BinaryTree<T>::_CreateTree(Node*& pRoot, const T array[], size_t size, size_t& index, const T& invalid)
{
	if ((array[index] != invalid) && (index < size))
	{
		pRoot = new Node(array[index]);
		_CreateTree(pRoot->m_pLeft, array, size, ++index, invalid);
		_CreateTree(pRoot->m_pRight, array, size, ++index, invalid);
	}
}

template <typename T>
BinaryTreeNode<T>* BinaryTree<T>::_CopyBinaryTree(Node* pRoot)
{
	Node* pNewRoot = NULL;
	if (pRoot)
	{
		pNewRoot = new Node(pRoot->m_data);
		pNewRoot->m_pLeft = _CopyBinaryTree(pRoot->m_pLeft);
		pNewRoot->m_pRight = _CopyBinaryTree(pRoot->m_pRight);
	}
	return pNewRoot;
}

template <typename T>
void BinaryTree<T>::_Destroy(Node*& pRoot)//�����
{
	if (pRoot)
	{	
		_Destroy(pRoot->m_pLeft);
		_Destroy(pRoot->m_pRight);
		delete pRoot;
		pRoot = nullptr;
	}
}

template <typename T>
void BinaryTree<T>::_PreOrder_1(Node* pRoot)//�ݹ�ʵ�֣�ǰ�����
{
	if (pRoot)
	{
		cout << pRoot->m_data << " ";
		_PreOrder_1(pRoot->m_pLeft);
		_PreOrder_1(pRoot->m_pRight);
	}
}
template <typename T>
void BinaryTree<T>::_PreOrder_2(Node* pRoot)//�ǵݹ�ʵ�֣�ǰ�����������ջʵ�֣�
{
	if (nullptr == pRoot)//����
		return ;
	stack<Node*> s;
	s.push(pRoot);

	while (!s.empty())
	{
		Node* pTemp = s.top();
		cout << pTemp->m_data << " ";
		s.pop();//pop����push֮ǰ������ջ��LIFO����

		if (pTemp->m_pRight)
			s.push(pTemp->m_pRight);//һ��Ҫ�ȴ��������������������������Ϊջ��LIFO����
		if (pTemp->m_pLeft)
			s.push(pTemp->m_pLeft);
	}
}

template <typename T>
void BinaryTree<T>::_InOrder_1(Node* pRoot)//�ݹ�ʵ�֣��������
{
	if (pRoot)
	{
		_InOrder_1(pRoot->m_pLeft);
		cout << pRoot->m_data << " ";
		_InOrder_1(pRoot->m_pRight);
	}
}
template <typename T>
void BinaryTree<T>::_InOrder_2(Node* pRoot)//�ǵݹ�ʵ�֣��������(1,�ҵ�������ߵĽڵ㣬������·�� 2�����ʵ�ǰ�ڵ㣬��������������Ϊ���ڵ㡣3���ظ�12)
{	
	if (nullptr == pRoot)
		return;

	stack<Node*> s;
	Node* pCur = pRoot;

	while (!s.empty() || pCur)//ע�⣺�������������Ϊ����������������ڵ��ջ֮�󣬻������������
	{
		while (pCur)
		{
			s.push(pCur);
			pCur = pCur->m_pLeft;
		}

		Node* pTemp = s.top();
		cout << pTemp->m_data << " ";
		s.pop();

		pCur = pTemp->m_pRight;
	}
}

template <typename T>
void BinaryTree<T>::_PostOrder(Node* pRoot)//�������
{
	if (pRoot)
	{
		_PostOrder(pRoot->m_pLeft);
		_PostOrder(pRoot->m_pRight);
		cout << pRoot->m_data << " ";
	}
}

template <typename T>
void BinaryTree<T>::_LevelOrder(Node* pRoot)//�������(���ö���ʵ��)
{	/*
	��ͼ��⣺
	1���Ƚ����ڵ�����У�
	2������ѭ�������׽������У������ֵ��
	3���������Һ��ӽڵ�����У�
	4������2-3ѭ����ֱ������Ϊ��
	*/
	if (!pRoot)
		return;

	queue<Node*> q;
	q.push(pRoot);

	while (!q.empty())
	{
		Node* pCur = q.front();
		q.pop();
		cout << pCur->m_data << " ";
		
		if (pCur->m_pLeft)
			q.push(pCur->m_pLeft);

		if (pCur->m_pRight)
			q.push(pCur->m_pRight);
	}
}

#endif //_BINARYTREE_H_