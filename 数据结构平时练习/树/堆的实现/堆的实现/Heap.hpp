#pragma once
#ifndef _HEAP_H_
#define _HEAP_H_

#include <iostream>
#include <vector>
using namespace std;

template<class T>
class Heap
{
public:
	// 创建一个空堆
	Heap()
	{}
	Heap(const T array[], size_t size);
	size_t Size()const;
	bool Empty()const;
	void Insert(const T& ata); 
	void Remove();

protected:
	void _AdjustDown(size_t parent);
	void _AdjustUp(size_t child);

protected:
	std::vector<T> _heap;
};

template <typename T>
Heap<T>::Heap(const T array[], size_t size)
{
	if (nullptr == array)
		return;

	_heap.resize(size);//重置vector大小

	for (int idx = size-1; idx >= 0; --idx)
	{
		_heap[idx] = array[idx];
	}
}

#endif //_HEAP_H_