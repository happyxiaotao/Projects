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

//逆向打印链表
void PrintFromTail2Head(Node* pHead)
{
	if (pHead)
	{
		PrintFromTail2Head(pHead->_pNext);
		cout << pHead->_data << "->";
	}
}

//逆向打印数组元素
void PrintArray(int* array, int size)
{
	if (size)
	{
		cout << array[size - 1] << "->";
		PrintArray(array, size-1);//与打印链表的区别在于数组可以由偏移确定位置，而链表只能遍历
	}
}

//逆向销毁链表
void DestroyFromTail2Head(Node*& pHead)//注意参数是一级指针引用或二级指针
{
	if (pHead)
	{
		DestroyFromTail2Head(pHead->_pNext);
		delete pHead;
		pHead = nullptr;
	}
}

//逆向查找值为data的节点
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

//递归实现二分查找(下标从0开始)
int BinarySearch(int* array, int left, int right, int data)
{
	assert(array);

	if (left <= right)
	{
		int mid = left + ((right - left) >> 1);

		if (array[mid] == data)//注意：在三者顺序上，先判断执行语句少的条件，后判断概率大的条件。
			return mid;
		else if (array[mid] > data)	//所以先判断array[mid]=data的条件，而后两种情况位置没有限制
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