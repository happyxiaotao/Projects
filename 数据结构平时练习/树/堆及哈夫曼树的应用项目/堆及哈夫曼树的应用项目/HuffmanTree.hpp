#pragma once
#ifndef _HUFFMANTREE_H_
#define _HUFFMANTREE_H_

#include "heap.hpp"

template <typename T>
struct HuffmanTreeNode
{
	HuffmanTreeNode(/*const T& data, */const T& weight)
		:_pLeft(nullptr)
		,_pRight(nullptr)
		,_weight(weight)
		,_data(weight)
	{}

	HuffmanTreeNode<T>* _pLeft;
	HuffmanTreeNode<T>* _pRight;
	T _weight;
	T _data;
};

template <typename T>
class HuffmanTree
{
	typedef HuffmanTreeNode<T> Node;
public:
	HuffmanTree()
		:_pRoot(nullptr)
	{}
	HuffmanTree(const T array[], size_t size, const T& invalid)
		:_pRoot(nullptr)
	{
		_CreateHuffmanTree(array, size, invalid);
	}

private:
	void _CreateHuffmanTree(const T array[], size_t size, const T& invalid);
private:
	Node* _pRoot;
};

template <typename T>
struct Less<T *>//�ػ�Ϊָ�����ͣ���Ϊ��ָ�����ݽ��бȽϵıȽ�����
{
	bool operator() (const T* lhs, const T* rhs)
	{
		return lhs->_weight < rhs->_weight;
	}
};

template <typename T>
void HuffmanTree<T>::_CreateHuffmanTree(const T array[], size_t size, const T& invalid)
{
	assert(array);

	if (1 == size)//��ֻ��һ���ڵ��ʱ��
	{
		_pRoot = new Node(array[0]);
		return ;
	}
	
	Heap<Node*, Less<Node*>> hp;//����С�Ѵ洢Ȩֵ������ÿ��ȡ��Ȩֵ��С�Ľڵ㣩
	for (size_t i = 0; i < size; ++i)
	{
		if (array[i] != invalid)
		{
			Node* pTemp = new Node(array[i]);
			hp.Insert(pTemp);
		}
	}

	Node* pParent = nullptr;//��ʱ˫�׽��

	//���ж���ڵ�ʱ
	while (1 < hp.Size())//��С����ֻʣ��һ��Ԫ��ʱ����Ϊ������������㣬���������������
	{
		Node* pLeft = hp.Top();//ȡ������Ȩֵ��С��Ԫ�أ��Ѷ�Ԫ�أ�
		hp.Remove();

		Node* pRight = hp.Top();
		hp.Remove();

		pParent = new Node(pLeft->_weight + pRight->_weight);//��������СȨֵ֮�����ڽڵ㣬��Ϊ˫��

		pParent->_pLeft = pLeft;//ȨֵС�������
		pParent->_pRight = pRight;//Ȩֵ������ұ�

		hp.Insert(pParent);//����С����
	}

	_pRoot = pParent;
}

#endif //_HUFFMANTREE_H_

