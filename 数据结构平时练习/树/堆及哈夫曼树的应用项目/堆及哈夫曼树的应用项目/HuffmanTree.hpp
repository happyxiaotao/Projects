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
	HuffmanTree(const T& array[], size_t size, const T& invalid)
		:_pRoot(nullptr)
	{
		_pRoot = _CreateHuffmanTree(array, size, invalid);
	}

private:
	Node* _CreateHuffmanTree(const T& array[], size_t size, const T& invalid);
private:
	Node* _pRoot;
};

template <typename T>
HuffmanTreeNode<T>* HuffmanTree<T>::_CreateHuffmanTree(const T& array[], size_t size, const T& invalid)
{
	assert(nullptr != array);

	if (1 == hp.Size())//当只有一个节点的时候
	{
		_pRoot = new Node(array[0]);
		hp.Remove();
	}
	
	Heap<T, Less<T>> hp(array, size, invalid);//采用小堆存储权值
	//当有多个节点时
	while (1 < hp.Size())
	{
		Node* pLeft = new Node(hp.Top());//取出两个权值最小的元素（堆顶元素）
		hp.Remove();

		Node* pRight = new Node(hp.Top());
		hp.Remove();

		Node* pParent = new Node(pLeft->_weight + pRight->_weight);
		hp.Insert(pParent->_weight);

		pParent->_pLeft = pLeft;
		pParent->_pRight = pRight;
	}
}

#endif //_HUFFMANTREE_H_

