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
private:
	T _data;
	BinaryTreeThNode<T>* _pLeft;
	BinaryTreeThNode<T>* _pRight;
	PointFlag _leftThread;
	PointFlag _rightThread;
};

template <typename T>
class BinaryTreeTh
{
	typedef BinaryTreeThNode Node;
public:
	BinaryTreeTh()
		: _pRoot(nullptr)
	{}
	
	BinaryTreeTh(const T array[], size_t size, const T& invalid)//������ͨ������
	{
		size_t index = 0;
		_CreateTree(_pRoot, array, size, index, invalid);
	}

	void PreThreading()//ǰ�����������������
	{
		Node* prev = nullptr;
		_PreThreading(_pRoot, prev);
	}

	void InThreading()//�������������������
	{
		Node* prev = nullptr;
		_InThreading(_pRoot, prev);
	}

	void PostThreading()//�������������������
	{
		Node* prev = nullptr;
		_PostThreading(_pRoot, prev);
	}

	void PreOrder();//ǰ���������������

	void InOrder();//�����������������

	void PostOrder();//�����������������

private:
	void _CreateTree(Node* &pRoot, const T array[], size_t size, size_t& index, const T& invalid);//����������

	void _PreThreading(Node* pRoot, Node*& prev);//ǰ�����������������

	void _InThreading(Node* pRoot, Node*& prev);//�������������������

	void _PostThreading(Node* pRoot, Node*& prev);//�������������������
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

#endif //_BINARYTREETH_H_