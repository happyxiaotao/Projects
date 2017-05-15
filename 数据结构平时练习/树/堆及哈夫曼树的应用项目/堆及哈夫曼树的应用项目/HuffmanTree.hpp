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
struct Less<T *>//特化为指针类型（作为将指针内容进行比较的比较器）
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

	if (1 == size)//当只有一个节点的时候
	{
		_pRoot = new Node(array[0]);
		return ;
	}
	
	Heap<Node*, Less<Node*>> hp;//采用小堆存储权值（方便每次取出权值最小的节点）
	for (size_t i = 0; i < size; ++i)
	{
		if (array[i] != invalid)
		{
			Node* pTemp = new Node(array[i]);
			hp.Insert(pTemp);
		}
	}

	Node* pParent = nullptr;//临时双亲结点

	//当有多个节点时
	while (1 < hp.Size())//当小堆中只剩下一个元素时，即为哈夫曼树根结点，哈夫曼树构建完毕
	{
		Node* pLeft = hp.Top();//取出两个权值最小的元素（堆顶元素）
		hp.Remove();

		Node* pRight = hp.Top();
		hp.Remove();

		pParent = new Node(pLeft->_weight + pRight->_weight);//生成两最小权值之和坐在节点，作为双亲

		pParent->_pLeft = pLeft;//权值小的在左边
		pParent->_pRight = pRight;//权值大的在右边

		hp.Insert(pParent);//插入小堆中
	}

	_pRoot = pParent;
}

#endif //_HUFFMANTREE_H_

