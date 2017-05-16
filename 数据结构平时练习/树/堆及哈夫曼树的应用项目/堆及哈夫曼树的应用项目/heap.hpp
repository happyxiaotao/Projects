#pragma once
#ifndef _HEAP_HPP_
#define _HEAP_HPP_

#include <vector>
#include <assert.h>
using namespace std;

//利用仿函数，模拟实现比较器
template <typename T>
struct Greater
{
	bool operator() (const T& lhs, const T& rhs)
	{
		return lhs > rhs;
	}
};
template <typename T>
struct Less
{
	bool operator() (const T& lhs, const T& rhs)
	{
		return lhs < rhs;
	}
};

//当第二个参数是类模板是，传入按照Heap<int, Com> hp传入
//template <typename T, template<typename T> class Compare>
//当第二个参数是类模板的实例时，参入按照Heap<int, Com<int> >传入
template<typename T, typename Compare = Less<T>>
class Heap
{
public:
	// 创建一个空堆
	Heap()
	{}
	Heap(const T array[], size_t size, const T& invalid);

	size_t Size()const
	{
		return _heap.size();
	}
	bool Empty()const
	{
		return _heap.empty();
	}

	T& Top()
	{
		assert(!_heap.empty());
		return _heap[0];
	}
	const T& Top()const
	{
		assert(!_heap.empty());
		return _heap[0];
	}

	void Insert(const T& data);//插入元素
	void Remove();//删除堆顶元素
	void Print();//按层序打印堆中元素

protected:
	void _AdjustDown(size_t parent);
	void _AdjustUp(size_t child);

protected:
	std::vector<T> _heap;
};

template <typename T, typename Compare = Less<T>>
Heap<T, Compare>::Heap(const T array[], size_t size, const T& invalid)
{
	assert(nullptr == array);

	_heap.resize(size);//改变堆的大小

	for (size_t i = 0; i < size; ++i)
		if (array[i] != invalid)
			_heap.push_back(array[i]);//保存数据

	for (int i = ((size - 2) >> 1); i >= 0; --i)
		_AdjustDown(i);		//向下调整
}

template <typename T, typename Compare = Less<T>>
void Heap<T, Compare>::_AdjustDown(size_t parent)
{
	size_t child = parent * 2 + 1;
	size_t size = _heap.size();

	while (child < size)
	{
		Compare com;//建立比较器
		if ((child + 1 < size) && com(_heap[child + 1], _heap[child]))//找到左右孩子中的最小的孩子下标
			++child;

		if (com(_heap[child], _heap[parent]))//如果根结点值小于左右孩子中最小节点值，则交换值
		{
			std::swap(_heap[child], _heap[parent]);
			parent = child;		//重置双亲与孩子节点进行循环
			child = parent * 2 + 1;
		}
		else
			return;//无需调整，直接退出
	}
}

template <typename T, typename Compare = Less<T>>
void Heap<T, Compare>::Insert(const T& data)
{
	_heap.push_back(data);
	
	if (_heap.size() > 1)//堆中元素不止一个节点
		_AdjustUp(_heap.size()-1);//向上调整，从最后一个节点开始
}

template<typename T, typename Compare = Less<T>>
void Heap<T, Compare>::_AdjustUp(size_t child)
{
	size_t size = _heap.size();
	size_t parent = ((child - 1) >> 1);

	while (child != 0)//孩子节点不能为0，为0时，没有双亲结点
	{
		Compare com;
		if (com(_heap[child], _heap[parent]))//和双亲结点比较大小
		{
			std::swap(_heap[child], _heap[parent]);//孩子节点值小于双亲结点时，交换两节点
			child = parent;		//孩子结点向上调整
			parent = (child - 1) >> 1;
		}
		else
			return;//无需调整，直接退出
	}
}

template <typename T, typename Compare = Less<T>>
void Heap<T, Compare>::Remove()//删除节点
{/*删除堆顶元素
 1，堆为空
 2，堆不为空
 将第一个和最后一个元素交换（考虑两者相等的情况）
 删除此时的最后一个结点
 从此时根结点向下调整
 */
	assert(!_heap.empty());//空堆
	size_t last = _heap.size() - 1;
	
	std::swap(_heap[last], _heap[0]);//交换两个元素
	_heap.pop_back();	//删除最后一个元素
	_AdjustDown(0);//从根结点向下调整
}

template <typename T, typename Compare = Less<T>>
void Heap<T, Compare>::Print()//按层序，打印堆中元素
{
	for (size_t i = 0; i < _heap.size(); ++i)
		cout << _heap[i] << " ";
	cout << endl;
}

#endif //_HEAP_HPP_


void Test1()
{

	//int arr[] = {9,8,7,6,5,4,3,2,1};
	//Heap<int, Less<int>> hp(arr, sizeof(arr) / sizeof(arr[0]));//创建小堆
	//Heap<int, Less> hp(arr, sizeof(arr) / sizeof(arr[0]));//当参数是类模板时

	int arr[] = { 1,3,5,7,9,2,4,6,8,10 };
	Heap<int, Greater<int>> hp(arr, sizeof(arr) / sizeof(arr[0]), -1);//创建大堆
	hp.Print();

	hp.Insert(0);
	hp.Print();

	hp.Remove();
	hp.Print();
}