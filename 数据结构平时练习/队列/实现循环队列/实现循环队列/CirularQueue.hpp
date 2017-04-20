#pragma once
#ifndef _CIRULARQUEUE_H_
#define _CIRULARQUEUE_H_

#include <iostream>
using namespace std;

//ѭ�����У����д�С�̶���������һ����Ԫ������ʹ�������ж�ѭ���б�Ŀջ�����״̬
//����Ϊ��ʱ:m_front = m_rear;������ʱ��(m_rear+1)%m_capacity = m_front.
//����ѭ��������Ԫ�ظ�����(m_rear+m_capacity-m_front)%m_capacity;
template <typename T>
class CirQueue
{
public:
	CirQueue();
	~CirQueue();

	void Push(const T& data);//�����
	void Pop();//������
	bool Empty()//�ж�ѭ�������Ƿ�Ϊ��
	size_t Size();//����ѭ������Ԫ�ظ���
	T& Front();//����ѭ��ͷԪ��
	T& Back();//����ѭ������βԪ��
private:
	bool CheckCapacity();//�ж�ѭ�������Ƿ�����
private:
	T* m_pData;//ָ��һ�������ռ�
	size_t m_front;//����ͷ���(��0��ʼ)(���Ӧ�ĵ�Ԫ��Զ��ʾ�ճ�������һ��)
	size_t m_rear;//����β���(��0��ʼ)
	size_t m_capacity;//ѭ�������������

};

template <typename T>
CirQueue<T>::CirQueue()
	: m_pData(new T[10])
	, m_front(0)
	, m_rear(0)
	, m_capacity(10)
{
	memset(m_pData, 0, m_capacity*sizeof(T));//���пռ丳Ϊ��
}

template <typename T>
CirQueue<T>::~CirQueue()
{
	if (m_pData)
	{
		delete[] m_pData;
		m_pData = nullptr;//��ϰ��
		m_front = 0;
		m_rear = 0;
		m_capacity = 0;
	}
}

//�ж�ѭ�������Ƿ�����
template <typename T>
bool CirQueue<T>::CheckCapacity()
{
	return (m_rear+1)%m_capacity != m_front;
}
//�ж�ѭ�������Ƿ�Ϊ��
template <typename T>
bool CirQueue<T>::Empty()
{
	return m_rear == m_front;
}
//Ԫ�������
template <typename T>
void CirQueue<T>::Push(const T& data)
{
	if (CheckCapacity())
	{
		m_pData[++m_rear] = data;
		m_rear %= m_capacity;//��Ϊ��ѭ�����У����Կ���ѭ��
	}
	else
		cerr << "CirQueue is full !" << endl;
}

template <typename T>
void CirQueue<T>::Pop()
{
	if (!Empty())
		m_front = (m_front + 1) % m_capacity;
	else
		cerr << "CirQueue is empyt !" << endl;
}

template <typename T>
size_t CirQueue<T>::Size()
{
	return (m_rear + m_capacity - m_front)%m_capacity;//m_rear,m_capacity,m_front����size_t,�����ȼӺ����
}

template <typename T>
T& CirQueue<T>::Front()
{
	 if (!Empty())
	 {
		 size_t head = (m_front + 1) % m_capacity;//m_frontָ�����Զ���ǿճ�������һ����Ԫ��Ӧ���±�
		 return m_pData[head];
	 }
	 cerr << "CirQueue is empty !" << endl;
	 exit(1);
}

template <typename T>
T& CirQueue<T>::Back()
{
	if (!Empty())
		return m_pData[m_rear];
	cerr << "CirQueue is empty !" << endl;
	exit(2);
}

#endif //_CIRULARQUEUE_H_