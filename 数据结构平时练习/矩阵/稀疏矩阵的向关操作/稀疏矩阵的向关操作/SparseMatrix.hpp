#pragma once
#ifndef _SPARSEMATRIX_H_
#define _SPARSEMATRIX_H_

#include <iostream>
#include <vector>
#include <assert.h>
using namespace std;

template<class T>
class SparseMatrix
{
	template<class T>
	struct Trituple//封装一个三元数组，存储稀疏矩阵中每个元素的信息
	{
		Trituple(int row = 0, int col = 0, const T& value = T())
			: m_row(row)
			, m_col(col)
			, m_value(value)
		{}
		size_t m_row;
		size_t m_col;
		T m_value;
	};

public:
	// 
	SparseMatrix(T* array, size_t row, size_t col, const T& invalid);

	~SparseMatrix();

	// 访问矩阵中的元素
	T& Access(int row, int col);
	const T& Access(int row, int col)const;

	template<class T>
	friend ostream& operator<<(ostream& _cout, const SparseMatrix<T>& sm);


	//给出两种逆置方法的时间复杂度
	// 稀疏矩阵的转置
	SparseMatrix<T> Transport();

	// 稀疏矩阵的快速转置
	SparseMatrix<T> FastTransport();

	// 两个矩阵相加
	SparseMatrix<T> operator+(const SparseMatrix<T>& sp);

private:
	vector<Trituple<T>> m_sm;
	size_t m_row;
	size_t m_col;
	T m_invalid;
};

template <typename T>
SparseMatrix<T>::SparseMatrix(T* array, size_t row, size_t col, const T& invalid)
	: m_row(row)
	, m_col(col)
	, m_invalid(invalid)
{
	if (array)
	{
		for (size_t i = 0; i < row; ++i)
			for (size_t j = 0; j < col; ++j)
				if (array[i*col + j] != invalid)
					m_sm.push_back(Trituple<T>(i, j, array[i*col + j]));
	}
}

template <typename T>
SparseMatrix<T>::~SparseMatrix()
{
	if (!m_sm.empty())
	{
		m_sm.clear();
		m_row = 0;
		m_col = 0;
	}
}

// 访问矩阵中的元素
template <typename T>
T& SparseMatrix<T>::Access(int row, int col)
{
	return const_cast<T&>(static_cast<const SparseMatrix<T>* const>(this)->Access(row, col));
}
template <typename T>
const T& SparseMatrix<T>::Access(int row, int col)const
{
	int count = m_sm.size();
	for (int i = 0; i < count; ++i)
		if (m_sm.at(i).m_row == row && m_sm.at(i).m_col == col)
			return m_sm.at(i).m_value;
	return m_invalid;
}

template<class T>
ostream& operator<<(ostream& out, const SparseMatrix<T>& sm)
{
	size_t count = 0;
	for (size_t i = 0; i < sm.m_row; ++i)
	{
		for (size_t j = 0; j < sm.m_col; ++j)
			if ((count < sm.m_sm.size()) && (sm.m_sm.at(count).m_row == i) && (sm.m_sm.at(count).m_col == j))
				cout << sm.m_sm.at(count++).m_value << " ";//加上count<sm.m_sm.size()，是为了防止访问越界。（有效元素访问完，还在往后访问）
			else
				cout << sm.m_invalid << " ";
		cout << endl;
	}
	return out;
}


//给出两种逆置方法的时间复杂度
// 稀疏矩阵的转置
//template <typename T>
//SparseMatrix<T> Transport()
//{}
//
// 稀疏矩阵的快速转置
//template <typename T>
//SparseMatrix<T> FastTransport()
//{}


// 两个矩阵相加
template <typename T>
SparseMatrix<T> SparseMatrix<T>::operator+(const SparseMatrix<T>& sp)
{
	assert((m_row == sp.m_row) && (m_col == sp.m_col) && (m_invalid == sp.m_invalid));

	SparseMatrix<T> temp(nullptr, m_row, m_col, m_invalid);
	size_t len_left = m_sm.size();
	size_t len_right = sp.m_sm.size();
	size_t i = 0;
	size_t j = 0;

	while ((i < len_left) && (j < len_right))
	{
		Trituple<T> trituple_left = m_sm.at(i);
		Trituple<T> trituple_right = sp.m_sm.at(j);
		if ((trituple_left.m_row < trituple_right.m_row) || (trituple_left.m_col < trituple_right.m_col))
		{
			temp.m_sm.push_back(trituple_left);//先存当前稀疏矩阵(*this)（左操作数）中的元素
			++i;
		}
		else if ((trituple_left.m_row == trituple_right.m_row) && (trituple_left.m_col == trituple_right.m_col))
		{
			if (trituple_left.m_value + trituple_right.m_value != m_invalid)//两者相等，且和不是无效元素
				temp.m_sm.push_back(Trituple<T>(trituple_left.m_row, trituple_left.m_col, trituple_left.m_value + trituple_right.m_value));
			++i;
			++j;
		}
		else
		{
			temp.m_sm.push_back(trituple_right);//先存传入参数（右操作数）中的元素
			++j;
		}
	}

	if (i < len_left)
		while (i < len_left)
			temp.m_sm.push_back(m_sm.at(i++));
	else if (j < len_right)
		while (j < len_left)
			temp.m_sm.push_back(sp.m_sm.at(j++));

	return temp;
}


#endif //_SPARSEMATRIX_H_