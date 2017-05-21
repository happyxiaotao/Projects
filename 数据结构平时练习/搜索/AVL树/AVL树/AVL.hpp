#pragma once

#ifndef _AVL_H_
#define _AVL_H_

#include <iostream>
using namespace std;

template <typename K, typename V>
struct AVLTreeNode
{
	AVLTreeNode(const K& key, const V& value)
		:_pParent(nullptr)
		,_pRight(nullptr)
		,_pLeft(nullptr)
		,_key(key)
		,_value(value)
		,_bf(0)//ƽ������Ĭ��Ϊ0
	{}
	AVLTreeNode<K, V>* _pParent;
	AVLTreeNode<K, V>* _pRight;
	AVLTreeNode<K, V>* _pLeft;
	K _key;
	V _value;
	int _bf;//ƽ������
};




#endif //_AVL_H_