#pragma once
#ifndef _HEAP_HPP_
#define _HEAP_HPP_

#include <vector>
#include <assert.h>
using namespace std;

//���÷º�����ģ��ʵ�ֱȽ���
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

//���ڶ�����������ģ���ǣ����밴��Heap<int, Com> hp����
//template <typename T, template<typename T> class Compare>
//���ڶ�����������ģ���ʵ��ʱ�����밴��Heap<int, Com<int> >����
template<typename T, typename Compare = Less<T>>
class Heap
{
public:
	// ����һ���ն�
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

	void Insert(const T& data);//����Ԫ��
	void Remove();//ɾ���Ѷ�Ԫ��
	void Print();//�������ӡ����Ԫ��

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

	_heap.resize(size);//�ı�ѵĴ�С

	for (size_t i = 0; i < size; ++i)
		if (array[i] != invalid)
			_heap.push_back(array[i]);//��������

	for (int i = ((size - 2) >> 1); i >= 0; --i)
		_AdjustDown(i);		//���µ���
}

template <typename T, typename Compare = Less<T>>
void Heap<T, Compare>::_AdjustDown(size_t parent)
{
	size_t child = parent * 2 + 1;
	size_t size = _heap.size();

	while (child < size)
	{
		Compare com;//�����Ƚ���
		if ((child + 1 < size) && com(_heap[child + 1], _heap[child]))//�ҵ����Һ����е���С�ĺ����±�
			++child;

		if (com(_heap[child], _heap[parent]))//��������ֵС�����Һ�������С�ڵ�ֵ���򽻻�ֵ
		{
			std::swap(_heap[child], _heap[parent]);
			parent = child;		//����˫���뺢�ӽڵ����ѭ��
			child = parent * 2 + 1;
		}
		else
			return;//���������ֱ���˳�
	}
}

template <typename T, typename Compare = Less<T>>
void Heap<T, Compare>::Insert(const T& data)
{
	_heap.push_back(data);
	
	if (_heap.size() > 1)//����Ԫ�ز�ֹһ���ڵ�
		_AdjustUp(_heap.size()-1);//���ϵ����������һ���ڵ㿪ʼ
}

template<typename T, typename Compare = Less<T>>
void Heap<T, Compare>::_AdjustUp(size_t child)
{
	size_t size = _heap.size();
	size_t parent = ((child - 1) >> 1);

	while (child != 0)//���ӽڵ㲻��Ϊ0��Ϊ0ʱ��û��˫�׽��
	{
		Compare com;
		if (com(_heap[child], _heap[parent]))//��˫�׽��Ƚϴ�С
		{
			std::swap(_heap[child], _heap[parent]);//���ӽڵ�ֵС��˫�׽��ʱ���������ڵ�
			child = parent;		//���ӽ�����ϵ���
			parent = (child - 1) >> 1;
		}
		else
			return;//���������ֱ���˳�
	}
}

template <typename T, typename Compare = Less<T>>
void Heap<T, Compare>::Remove()//ɾ���ڵ�
{/*ɾ���Ѷ�Ԫ��
 1����Ϊ��
 2���Ѳ�Ϊ��
 ����һ�������һ��Ԫ�ؽ���������������ȵ������
 ɾ����ʱ�����һ�����
 �Ӵ�ʱ��������µ���
 */
	assert(!_heap.empty());//�ն�
	size_t last = _heap.size() - 1;
	
	std::swap(_heap[last], _heap[0]);//��������Ԫ��
	_heap.pop_back();	//ɾ�����һ��Ԫ��
	_AdjustDown(0);//�Ӹ�������µ���
}

template <typename T, typename Compare = Less<T>>
void Heap<T, Compare>::Print()//�����򣬴�ӡ����Ԫ��
{
	for (size_t i = 0; i < _heap.size(); ++i)
		cout << _heap[i] << " ";
	cout << endl;
}

#endif //_HEAP_HPP_


void Test1()
{

	//int arr[] = {9,8,7,6,5,4,3,2,1};
	//Heap<int, Less<int>> hp(arr, sizeof(arr) / sizeof(arr[0]));//����С��
	//Heap<int, Less> hp(arr, sizeof(arr) / sizeof(arr[0]));//����������ģ��ʱ

	int arr[] = { 1,3,5,7,9,2,4,6,8,10 };
	Heap<int, Greater<int>> hp(arr, sizeof(arr) / sizeof(arr[0]), -1);//�������
	hp.Print();

	hp.Insert(0);
	hp.Print();

	hp.Remove();
	hp.Print();
}