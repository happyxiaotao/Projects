#include "heap.hpp"
#include "priorityQueue.hpp"
#include "HuffmanTree.hpp"
#include <iostream>

using namespace std;

void Test1();
void Test2();

int main()
{
//	Test1();

	Test2();

	system("pause");
	return 0;
}

void Test1()
{
	
	//int arr[] = {9,8,7,6,5,4,3,2,1};
	//Heap<int, Less<int>> hp(arr, sizeof(arr) / sizeof(arr[0]));//创建小堆
	//Heap<int, Less> hp(arr, sizeof(arr) / sizeof(arr[0]));//当参数是类模板时

	int arr[] = {1,3,5,7,9,2,4,6,8,10};
	Heap<int, Greater<int>> hp(arr, sizeof(arr)/sizeof(arr[0]), -1);//创建大堆
	hp.Print();

	hp.Insert(0);
	hp.Print();

	hp.Remove();
	hp.Print();

	cout << endl;
}

void Test2()
{
	int arr[] = {1,3,5,7};
	HuffmanTree<int> ht(arr, sizeof(arr)/sizeof(arr[0]), -1);
}