#pragma once

#define _CRT_SECURE_NO_WARNINGS

#ifndef _HUFFMANCOMPRESS_H_
#define _HUFFMANCOMPRESS_H_

#include "HuffmanTree.hpp"
#include <string>
#include <iostream>
using namespace std;

struct CharInfo//保留每个字符信息
{
public:
	CharInfo(long count = 0)
		:_count(count)
	{}
public:
	//需要特化几个函数，方便构建哈夫曼树
	CharInfo operator + (const CharInfo& rhs)const
	{
		return CharInfo(_count + rhs._count);
	}
	bool operator < (const CharInfo& rhs)const
	{
		return _count < rhs._count;
	}
	bool operator == (const CharInfo& rhs)const
	{
		return _count == rhs._count;
	}
	bool operator != (const CharInfo& rhs)const
	{
		return !(*this == rhs);
	}

public:
	unsigned char _ch;
	long _count;
	string _strCode;
};

class HuffmanCompress
{
public:
	HuffmanCompress(string& fileName);//哈夫曼压缩
	void UnCompress();//哈夫曼解压缩
private:
	//统计文件中字符出现次数
	//保存各个字符的哈夫曼编码
	void GeneratorHuffmanCode(HuffmanTreeNode<CharInfo>* pRoot, string& strCode);
	//重新对文件进行编码
	//向文件中写入一些编码信息
	void GeneratorConfigInfo(FILE* fOut;
private:
	CharInfo _FileInfo[256];//一共有256中不同的字符（汉字是由两个字符组成的）
};

HuffmanCompress::HuffmanCompress(string& fileName)
{/*
	哈夫曼文件压缩思路：
	1，遍历文件，统计256个字符出现次数
	2，利用字符及其出现次数创建哈夫曼树
	3，利用哈夫曼树找到每个字符的编码
	4，重新对文件进行编码
*/
	FILE* fIn = fopen(fileName.c_str(), "r");

	if (nullptr == fIn)
	{
		fputs("Open file error", stderr);
		cout << endl;
		return;
	}
	else
		cout << "Open file success" << endl;

	for (size_t i = 0; i <256; ++i)
		_FileInfo[i]._ch = i;//给256个字符节点赋值

	char* pReadBuff = new char[1024];//最多一次读取1024个字节（一次读取一个字符，效率低）
	while (true)	//统计各个字符出现次数
	{
		size_t readSize = fread(pReadBuff, 1, 1024, fIn);//readSize保存一次读取的实际个数

		if (0 == readSize)//没有读取到字符
			break;

		for (size_t i = 0; i < readSize; ++i)
			_FileInfo[pReadBuff[i]]._count++;
	}

	//构建哈夫曼树
	HuffmanTree<CharInfo> ht(_FileInfo, 256, CharInfo(0));

	//保存各个字符的哈夫曼编码
	string strCode;
	HuffmanTreeNode<CharInfo>* pRoot = ht.GetRoot();
	GeneratorHuffmanCode(pRoot, strCode);

	//对文件进行重新编码
	fseek(fIn, 0, SEEK_SET);//返回刚才打开文件的头部

	FILE* fOut = fopen("test.hfc", "w");
	char* pWriteBuff = new char[1024];//写入文件的缓存区。最多一次写入1024
	size_t writeCount = 0;//表示1024字节缓冲中，已经保存的字节数（满足1024字节，就一次写入文件中）
	char value = 0;//表示一个字节，用来保存8位二进制编码
	int pos = 0;//表示一个字节八位中已经使用了几位

	while (true)
	{
		size_t readSize = fread(pReadBuff, 1, 1024, fIn);

		if (readSize)
		{
			for (size_t i = 0; i < readSize; ++i)//遍历readBuff中的每一个字符
			{
				unsigned char ch = pReadBuff[i];//读入缓冲区中的一个字符

				string& strCode = _FileInfo[ch]._strCode;//当前字符对于编码的引用
				for (size_t i = 0; i < strCode.length(); ++i)
				{
					value <<= 1;//注意，先移位，后判断（避免：当最后一位0表示存储的编码二进制时，，以1异或导致编码错误）
					if (strCode[i] == '1')
						value |= 1;

					if (8 == ++pos)//pos增加1，并且判断当前字节是否已经存满，若存满了8位，就往writeBuff缓冲区中写入value
					{
						pWriteBuff[writeCount] = value;
						++writeCount;//缓冲区中，已经存储的字节个数加1
						pos = 0;//重新开始进行编码
					}
					if (1024 == writeCount)//判断缓冲区是否写满，写满就写入文件中
					{
						fwrite(pWriteBuff, 1, 1024, fOut);
						writeCount = 0;//重新开始计数
					}
				}

			}
		}
		else
			break;
	}

	//注意，存在文件读取完，但是，当前value中还有剩余位没有填充完毕，或者还有缓冲区不满1024字节还有内容没有写入文件中
	if (pos)//pos大于0，表示正在填充，因为当pos=8时，会将pos置位0
	{
		value <<= (8 - pos);//剩余比特补上0，写入writeBuff缓冲区中
		pWriteBuff[writeCount] = value;
		++writeCount;
	}
	//注意，pos和writeCount的判断语句，要分开写，不能写在一个判断中
	if (writeCount)//同pos
	{
		fwrite(pWriteBuff, 1, writeCount, fOut);//有多少，写入多少
	}

	//释放缓冲区
	delete[] pReadBuff;
	delete[] pWriteBuff;

	//关闭文件
	fclose(fIn);
	fclose(fOut);
}

//保存各个字符的哈夫曼编码
void HuffmanCompress::GeneratorHuffmanCode(HuffmanTreeNode<CharInfo>* pRoot, string& strCode)
{
	if (nullptr == pRoot)
		return;
	
	if (nullptr == pRoot->_pLeft && nullptr == pRoot->_pRight)
		_FileInfo[pRoot->_weight._ch]._strCode = strCode;

	GeneratorHuffmanCode(pRoot->_pLeft, strCode + '0');

	GeneratorHuffmanCode(pRoot->_pRight, strCode + '1');
}

void HuffmanCompress::UnCompress()
{}

#endif //_HUFFMANCOMPRESS_H_

