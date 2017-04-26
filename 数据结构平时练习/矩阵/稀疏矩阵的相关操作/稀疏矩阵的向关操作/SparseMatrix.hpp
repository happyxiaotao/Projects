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
	T& Access(int row, int col);
	const T& Access(int row, int col)const;

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

// ���ʾ����е�Ԫ��
template <typename T>
T& SparseMatrix<T>::Access(int row, int col)
{
	return const_cast<T&>(static_cast<const SparseMatrix<T>* const>(this)->Access(row, col));
}
template <typename T>
const T& SparseMatrix<T>::Access(int row, int col)const
{
	int count = m_sm.size();
	for (size_t i = 0; i < count; ++i)
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
				cout << sm.m_sm.at(count++).m_value << " ";//����count<sm.m_sm.size()����Ϊ�˷�ֹ����Խ�硣����ЧԪ�ط����꣬����������ʣ�
			else
				cout << sm.m_invalid << " ";
		cout << endl;
	}
	return out;
}


//�����������÷�����ʱ�临�Ӷ�
// ϡ������ת��(M��N�У�ʱ�临�Ӷ�O(M*MN))
template <typename T>
SparseMatrix<T> SparseMatrix<T>::Transport()
{
	SparseMatrix<T> temp(nullptr, m_col, m_row, m_invalid);

	for (size_t i = 0; i < m_col; ++i)
	{
		for (size_t j = 0; j < m_sm.size(); ++j)
			if (m_sm.at(j).m_col == i)
				temp.m_sm.push_back(Trituple<T>(m_sm.at(j).m_col, m_sm.at(j).m_row, m_sm.at(j).m_value));
	}

 	return temp;
}


 //ϡ�����Ŀ���ת��(M��N�У�ʱ�临�Ӷ�O(MN+N+MN))�Կռ任ʱ��ķ���
template <typename T>
SparseMatrix<T> SparseMatrix<T>::FastTransport()
{
	SparseMatrix<T> temp(nullptr, m_col, m_row, m_invalid);

	//�����ƣ�����������������Ĵ�С���������ֵ��
	//���ɴ������˽⵽��ֻ���ڱ���ʱȷ��ֵ�ı����ǳ������������ڼ�ȷ��ֵ�Ĳ��ǳ�������ʹ����const������const int a = v.size();��
	size_t RowCount[5] = { 0 };//ͳ��ת�ú�ÿһ����Ч���ݵĸ���
	size_t RowStart[6] = { 0 };//ͳ��ת�ú�ÿһ����Ч������ѹ���洢�еĳ�ʼλ��

	for (size_t i = 0; i < m_sm.size(); ++i)
		RowCount[m_sm.at(i).m_col]++;
	for (size_t i = 1; i < m_col; ++i)
		RowStart[i] = RowStart[i - 1] + RowCount[i - 1];

	temp.m_sm.resize(m_sm.size());

	for (size_t i = 0; i < m_sm.size(); ++i)
	{
		size_t idx = RowStart[m_sm.at(i).m_col]++;
		temp.m_sm.at(idx) = Trituple<T>(m_sm.at(i).m_col, m_sm.at(i).m_row, m_sm.at(i).m_value);
	}
	
	return temp;
}


// �����������
template <typename T>
SparseMatrix<T> SparseMatrix<T>::operator+(const SparseMatrix<T>& sp)
{
	assert((m_row == sp.m_row) && (m_col == sp.m_col) && (m_invalid == sp.m_invalid));
	//�ֱ��������ѹ�������е�Ԫ�أ�������Ԫ���ھ����е����λ�ã��Լ���ͬλ������֮���Ƿ�����ЧԪ�أ���������ʱ���������
	SparseMatrix<T> temp(nullptr, m_row, m_col, m_invalid);
	size_t len_left = m_sm.size();
	size_t len_right = sp.m_sm.size();
	size_t i = 0;
	size_t j = 0;

	while ((i < len_left) && (j < len_right))
	{
		Trituple<T> trituple_left = m_sm.at(i);
		Trituple<T> trituple_right = sp.m_sm.at(j);
		
		if ((trituple_left.m_row < trituple_right.m_row) || ((trituple_left.m_row == trituple_right.m_row) && (trituple_left.m_col < trituple_right.m_col)))
		{
			temp.m_sm.push_back(trituple_left);//�ȴ浱ǰϡ�����(*this)������������е�Ԫ��
			++i;
		}
		else if ((trituple_left.m_row == trituple_right.m_row) && (trituple_left.m_col == trituple_right.m_col))
		{
			if (trituple_left.m_value + trituple_right.m_value != m_invalid)//������ȣ��ҺͲ�����ЧԪ��
				temp.m_sm.push_back(Trituple<T>(trituple_left.m_row, trituple_left.m_col, trituple_left.m_value + trituple_right.m_value));
			++i;
			++j;
		}
		else
		{
			temp.m_sm.push_back(trituple_right);//�ȴ洫��������Ҳ��������е�Ԫ��
			++j;
		}
	}

	if (i < len_left)
		while (i < len_left)
			temp.m_sm.push_back(m_sm.at(i++));
	else if (j < len_right)
		while (j < len_right)
			temp.m_sm.push_back(sp.m_sm.at(j++));

	return temp;
}


#endif //_SPARSEMATRIX_H_