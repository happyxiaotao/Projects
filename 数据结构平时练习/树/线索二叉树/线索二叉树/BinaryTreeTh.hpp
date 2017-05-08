#pragma once
#ifndef _BINARYTREETH_H_
#define _BINARYTREETH_H_

#include <iostream>
using namespace std;

enum PointFlag {LINK, THREAD};//���ʾָ������ָ�����ʾ�ĺ���
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
public:
	T _data;
	BinaryTreeThNode<T>* _pLeft;
	BinaryTreeThNode<T>* _pRight;
	PointFlag _leftThread;
	PointFlag _rightThread;
};

template <typename T>
class BinaryTreeTh
{
	typedef BinaryTreeThNode<T> Node;
public:
	BinaryTreeTh()
		: _pRoot(nullptr)
	{}
	
	BinaryTreeTh(const T array[], size_t size, const T& invalid)//������ͨ������
	{
		size_t index = 0;
		_CreateTree(_pRoot, array, size, index, invalid);
	}

	void PreThreading()//ǰ��������������
	{
		Node* prev = nullptr;
		_PreThreading(_pRoot, prev);
	}

	void InThreading()//����������������
	{
		Node* prev = nullptr;
		_InThreading(_pRoot, prev);
	}

	void PostThreading()//����������������
	{
		Node* prev = nullptr;
		_PostThreading(_pRoot, prev);
	}

	void PreOrder();//ǰ���������������

	void InOrder();//�����������������

	void PostOrder();//�����������������

private:
	void _CreateTree(Node* &pRoot, const T array[], size_t size, size_t& index, const T& invalid);//����������

	void _PreThreading(Node* pRoot, Node*& prev);//ǰ��������������

	void _InThreading(Node* pRoot, Node*& prev);//����������������

	void _PostThreading(Node* pRoot, Node*& prev);//����������������
private:
	Node* _pRoot;
};


template <typename T>//����������
void BinaryTreeTh<T>::_CreateTree(Node*& pRoot, const T array[], size_t size, size_t& index, const T& invalid)
{
	if ((index < size) && (array[index] != invalid))
	{
		pRoot = new Node(array[index]);

		_CreateTree(pRoot->_pLeft, array, size, ++index, invalid);
		_CreateTree(pRoot->_pRight, array, size, ++index, invalid);
	}
}

template <typename T>//ǰ��������������
void BinaryTreeTh<T>::_PreThreading(Node* pRoot, Node*& prev)
{
	/*
	����ǰ���������������������ǰ�����˳�򣺸�-��-�ҡ�������˳�򣺸�-��-�ң�
	ĳһ��㣺
		��ָ�������ӣ��ǿգ�/ǰ�����գ�
		��ָ�����Һ��ӣ��ǿգ�/��̣��գ�
	*/

	if (pRoot)
	{
		if (prev && (nullptr == pRoot->_pLeft))//������Ϊ��ʱ�����������ӣ�prev����Ϊ�գ�
		{
			pRoot->_pLeft = prev;
			pRoot->_leftThread = THREAD;
		}
		if (prev && (nullptr == prev->_pRight))//���Һ���Ϊ��ʱ���������Һ��ӣ�prev����Ϊ�գ�
		{
			prev->_pRight = pRoot;
			prev->_rightThread = THREAD;
		}
		
		prev = pRoot;//prevָ��������ʵĽ��

		if (LINK == pRoot->_leftThread)//����δ�����������������Ӳ�Ϊ�գ�����������������������������
			_PreThreading(pRoot->_pLeft, prev);

		if (LINK == pRoot->_rightThread)//�Һ���δ���������������Һ��Ӳ�Ϊ�գ��������Һ���������������������
			_PreThreading(pRoot->_pRight, prev);
	}
}

template <typename T>
void BinaryTreeTh<T>::_InThreading(Node* pRoot, Node*& prev)//����������������
{
	//��������������������--��--��

	if (pRoot)
	{
		prev = pRoot;

		if (LINK == pRoot->_leftThread)
			_InThreading(pRoot->_pLeft, prev);

		//��������ǰ�ڵ�
		if (prev && (nullptr == pRoot->_pLeft))//������������
		{
			pRoot->_pLeft == prev;
			pRoot->_leftThread = THREAD;
		}

		if (prev && (nullptr == prev->_pRight))//������������
		{
			prev->_pRight = pRoot;
			prev->_rightThread = THREAD;
		}
		if (LINK == pRoot->_rightThread)
			_InThreading(pRoot->_pRight, prev);
	}
}

template <typename T>
void BinaryTreeTh<T>::_PostThreading(Node* pRoot, Node*& prev)//����������������
{}

#endif //_BINARYTREETH_H_