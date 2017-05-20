#include "HuffmanCompress.hpp"

#include <iostream>
using namespace std;

int main()
{
//	Test1();

//	Test2();

	
	//int arr[] = { 0, 4, 0, 0 };
	//HuffmanTree<int> ht(arr, 4, 0);//只有一个节点的情况
	

	string fileName("HuffmanCompress_test.txt");
	HuffmanCompress hfc(fileName);
	hfc.UnCompress();

	//FILE* fIn = fopen("HuffmanCompress_test.txt", "r");

	//char* readBuff = new char[1024];

	//size_t readSize = fread(readBuff, 1, 1024, fIn);

	//FILE * fOut = fopen("HuffmanCompress_test.tttt", "w");
	//fwrite(readBuff, 1, readSize, fOut);

	system("pause");
	return 0;
}