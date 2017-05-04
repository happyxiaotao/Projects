#include <iostream>
#include <assert.h>
using namespace std;

typedef unsigned int DataType;
struct Node
{
public:
	DataType value;
	Node* _pNext;
};

//�����ӡ����
void PrintFromTail2Head(Node* pHead)
{
	if (pHead)
	{
		PrintFromTail2Head(pHead->_pNext);
		cout << pHead->_data << "->";
	}
}

//�����ӡ����Ԫ��
void PrintArray(int* array, int size)
{
	if (size)
	{
		cout << array[size - 1] << "->";
		PrintArray(array, size-1);//���ӡ����������������������ƫ��ȷ��λ�ã�������ֻ�ܱ���
	}
}

//������������
void DestroyFromTail2Head(Node*& pHead)//ע�������һ��ָ�����û����ָ��
{
	if (pHead)
	{
		DestroyFromTail2Head(pHead->_pNext);
		delete pHead;
		pHead = nullptr;
	}
}

//�������ֵΪdata�Ľڵ�
Node* FindFromTail2Head(Node* pHead, DataType data)
{
	if (pHead)
	{
		Node* temp = FindFromTail2Head(pHead->_pNext, data);

		if (temp)
			return temp;
		
		if (pHead->value == data)
			return pHead;
	}

	return nullptr;
}

//�ݹ�ʵ�ֶ��ֲ���(�±��0��ʼ)
int BinarySearch(int* array, int left, int right, int data)
{
	assert(array);

	if (left <= right)
	{
		int mid = left + ((right - left) >> 1);

		if (array[mid] == data)//ע�⣺������˳���ϣ����ж�ִ������ٵ����������жϸ��ʴ��������
			return mid;
		else if (array[mid] > data)	//�������ж�array[mid]=data�������������������λ��û������
			return BinarySearch(array, left, mid - 1, data);
		else
			return BinarySearch(array, mid+1, right, data);
	}

	return -1;
}


int main()
{

	system("pause");
	return 0;
}