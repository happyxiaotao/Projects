#pragma once

#ifndef _STACK_HPP_
#define _STACK_HPP_
#include <iostream>
#include <assert.h>
using namespace std;
//需要萃取的特性
struct TypeTrue
{
	bool Get()
	{
		return true;
	}
};
struct TypeFalse
{
	bool Get()
	{
		return false;
	}
};
//对不同的特性进行封装
template <typename T>
struct Traits
{
	typedef TypeFalse _Is_POD_Type;
};
template <>
struct Traits<char>
{
	typedef TypeTrue _Is_POD_Type;
};
template <>
struct Traits<int>
{
	typedef TypeTrue _Is_POD_Type;
};
//此处省略其他内置类型

//根据不同的特性进行拷贝
template <typename T>
void Copy(T* dest, const T* src, size_t size, TypeTrue type)
{
	assert(dest);
	assert(src);
	memcpy(dest, src, size*sizeof(T));
}

template <typename T>
void Copy(T* dest, const T* src, size_t size, TypeFalse type)
{
	assert(dest);
	assert(src);
	for (size_t idx = 0; idx < size; ++idx)
	{
		dest[idx] = src[idx];
	}
}

//模板栈
template <typename T>
class Stack
{
public:
	Stack();
	Stack(const Stack<T>& s);
	Stack<T>& operator = (const Stack<T>& s);
	~Stack();

	void Push(T);
	void Pop();
	bool Empty() const;
	T& Top();
private:
	void CheckCapacity();
private:
	T* m_pData;
	size_t m_size;
	size_t m_capacity;
};

template <typename T>
Stack<T>::Stack() :m_pData(new T[10]), m_size(0), m_capacity(10)
{
	memset(m_pData, 0, m_capacity*sizeof(T));
}

template <typename T>
Stack<T>::Stack(const Stack<T>& s) :m_pData(new T[s.m_capacity]), m_size(s.m_size), m_capacity(s.m_capacity)
{
	// isPOD//不是POD，进行深拷贝
	Copy(m_pData, s.m_pData, s.m_capacity, Traits<T>::_Is_POD_Type());
}

template <typename T>
Stack<T>& Stack<T>::operator = (const Stack<T>& s)
{
	if (this != &s)
	{
		T* ptemp = new T[s.m_capacity];
		Copy(ptemp, s.m_pData, s.m_capacity, Traits<T>::_Is_POD_Type());
		delete[] m_pData;
		m_pData = ptemp;
		ptemp = nullptr;
	}
	return *this;
}

template <typename T>
Stack<T>::~Stack()
{
	if (m_pData)
	{
		delete[] m_pData;
		m_size = 0;
		m_capacity = 0;
	}
}

template <typename T>
void Stack<T>::CheckCapacity()
{
	if (m_size >= m_capacity)
	{
		T* ptemp = new T[m_capacity * 2];
		m_capacity *= 2;
		Copy(ptemp, m_pData, m_size, Traits<T>::_Is_POD_Type());
		delete[] m_pData;
		m_pData = ptemp;
		ptemp = nullptr;
	}
}

template <typename T>
void Stack<T>::Push(T data)
{
	CheckCapacity();
	m_pData[m_size++] = data;
}

template <typename T>
void Stack<T>::Pop()
{
	if (!Empty())
		--m_size;
	else
	{
		cerr << "operator Pop error:Stack is Empty！" << endl;
		exit(1);
	}
}

template <typename T>
bool Stack<T>::Empty() const
{
	return 0 == m_size;
}

template <typename T>
T& Stack<T>::Top()
{
	if (!Empty())
		return m_pData[m_size - 1];
	else
	{
		cerr << "operator Top error:Stack is Empty！" << endl;
		return m_pData[0];
	}
}
#endif //_STACK_HPP_