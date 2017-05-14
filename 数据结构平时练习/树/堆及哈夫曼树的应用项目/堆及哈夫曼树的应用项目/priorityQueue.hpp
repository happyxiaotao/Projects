#pragma once
#ifndef _PRIORITYQUEUE_HPP_
#define _PRIORITYQUEUE_HPP_

#include "heap.hpp"

template <typename T, typename Compare = Less<T>>
class PriorityQueue
{
public:
	bool Empty()
	{
		return _pq.Empty();
	}
	size_t Size()
	{
		return _pq.Size();
	}
	T& Top()
	{
		return _pq.Top();
	}
	const T& Top()const
	{
		return _pq.Top();
	}
	void Push(T& data)
	{
		_pq.Insert();
	}
	void Pop()
	{
		_pq.Remove();
	}
private:
	Heap<T, Compare> _pq;//Ä¬ÈÏÐ¡¶Ñ
};

#endif //_PRIORITYQUEUE_HPP_