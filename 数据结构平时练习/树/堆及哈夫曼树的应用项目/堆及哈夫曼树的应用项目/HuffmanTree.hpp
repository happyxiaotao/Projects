#pragma once
#ifndef _HUFFMANTREE_H_
#define _HUFFMANTREE_H_

#include "heap.hpp"

template <typename T>
struct HuffmanTreeNode
{
	HuffmanTreeNode(const T& data, const T& weight)
		:_pLeft(nullptr)
		,_pRight(nullptr)
		,_weight(weight)
		,_data(data)
	{}

	HuffmanTreeNode<T>* _pLeft;
	HuffmanTreeNode<T>* _pRight;
	T _weight;
	T _data;
};

template <typename T, typename Compare = Less<T> >
class HuffmanTree
{
	typedef HuffmanTreeNode<T> Node;
public:
	HuffmanTree<T>
private:
	Node* _pRoot;
};

#endif //_HUFFMANTREE_H_

