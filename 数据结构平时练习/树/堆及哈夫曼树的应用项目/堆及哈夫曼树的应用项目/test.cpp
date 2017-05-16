#include "HuffmanCompress.hpp"

#include <iostream>
using namespace std;

int main()
{
//	Test1();

//	Test2();

	/*	int arr[] = {1,3,5,7};
	HuffmanTree<int> ht(arr, 4, 0);*/
	string fileName("test.txt");
	HuffmanCompress hfc(fileName);


	system("pause");
	return 0;
}