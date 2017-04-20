#pragma once
#ifndef _SPARSEMATRIX_H_
#define _SPARSEMATRIX_H_

#include <iostream>
#include <vector>
using namespace std;

template<class T>
class SparseMatrix
{
	template<class T>
	struct Trituple//��װһ����Ԫ���飬�洢ϡ�������ÿ��Ԫ�ص���Ϣ
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

	// ���ʾ����е�Ԫ��
	T& Acess(int row, int col);
	const T& Acess(int row, int col)const;

	template<class T>
	friend ostream& operator<<(ostream& _cout, const SparseMatrix<T>& sm);


	//�����������÷�����ʱ�临�Ӷ�
	// ϡ������ת��
	SparseMatrix<T> Transport();

	// ϡ�����Ŀ���ת��
	SparseMatrix<T> FastTransport();

	// �����������
	SparseMatrix<T> operator+(const SparseMatrix<T>& sp);

private:
	vector<Trituple<T>> m_sm;
	size_t m_row;
	size_t m_col;
	T m_invalid;
};

template <typename T>
SparseMatrix<T>::SparseMatrix(T* array, size_t row, size_t col, const T& invalid)
{
	if (array)
	{
		for (size_t i = 0; i < row; ++i)
			for (size_t j = 0; j < col; ++j)
				if (array[i*col + j] != invalid)
					m_sm.push_back(Trituple<T>(i, j, array[i*col + j]));
		m_row = row;
		m_col = col;
		m_invalid = invalid;
	}
	else
	{
		m_row = 0;
		m_col = 0;
		m_invalid = T();
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


// ���ʾ����е�Ԫ��
template <typename T>
T& SparseMatrix<T>::Acess(int row, int col)
{
	return const_cast<T&>(static_cast<const SparseMatrix* const>(this)->Acess(row, col));
}

template <typename T>
const T& SparseMatrix<T>::Acess(int row, int col)const
{
}

template<class T>
ostream& operator<<(ostream& out, const SparseMatrix<T>& sm)
{
	for (size_t i = 0; i < sm.m_row; ++i)
	{
		for (size_t j = 0; j < sm.m_col; ++j)
			cout << sm.Acess(i, j);
		cout << endl;
	}
	return out;
}

//
//�����������÷�����ʱ�临�Ӷ�
// ϡ������ת��
//template <typename T>
//SparseMatrix<T> Transport()
//{}
//
// ϡ�����Ŀ���ת��
//template <typename T>
//SparseMatrix<T> FastTransport()
//{}
//
// �����������
//template <typename T>
//SparseMatrix<T> operator+(const SparseMatrix<T>& sp)
//{}


#endif //_SPARSEMATRIX_H_