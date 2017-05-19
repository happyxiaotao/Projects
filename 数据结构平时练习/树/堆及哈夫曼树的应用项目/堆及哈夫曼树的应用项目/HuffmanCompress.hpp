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
	char _ch;
	long _count;
	string _strCode;
};

class HuffmanCompress
{
public:
	HuffmanCompress(const string& fileName);//哈夫曼压缩
	void UnCompress();//哈夫曼解压缩
private:
	//统计文件中字符出现次数
	void GetEachCharCount(FILE*& fIn);
	//保存各个字符的哈夫曼编码
	void GeneratorHuffmanCode(HuffmanTreeNode<CharInfo>* pRoot, string& strCode);
	//向文件中写入一些编码信息
	void WriteConfigInfoInFile(FILE*& fOut, const string& fileName);
	//将字符编码写入文件
	void WriteCodeInFile(FILE*& fIn, FILE*& fOut);
private:
	CharInfo _FileInfo[256];//一共有256中不同的字符（汉字是由两个字符组成的）
};

HuffmanCompress::HuffmanCompress(const string& fileName)
{/*
	哈夫曼文件压缩思路：
	1，遍历文件，统计256个字符出现次数
	2，利用字符及其出现次数创建哈夫曼树
	3，利用哈夫曼树找到每个字符的编码
	4，重新对文件进行编码
*/

	//打开将要读取内容的文件
	FILE* fIn = fopen(fileName.c_str(), "r");
	if (nullptr == fIn)
	{
		cout << "Open file " << fileName << " error!" << endl;
		return;
	}
	else
		cout << "Open file " << fileName << " success!" << endl;

	//1，获取各个字符出现次数
	GetEachCharCount(fIn);

	//2，构建哈夫曼树
	HuffmanTree<CharInfo> ht(_FileInfo, 256, CharInfo(0));

	//3，保存各个字符的哈夫曼编码
	string strCode;
	HuffmanTreeNode<CharInfo>* pRoot = ht.GetRoot();
	GeneratorHuffmanCode(pRoot, strCode);//生成各个字符的编码

	//4，接下来，对文件进行重新编码
	fseek(fIn, 0, SEEK_SET);//返回刚才打开文件的头部

	//打开将要写入内容的文件
	FILE* fOut = fopen("HuffmanCompress_test.htc", "w");
	if (nullptr == fOut)
	{
		cout << "Open file " << "HuffmanCompress_test.htc" << " error!" << endl;
		return;
	}
	else
		cout << "Open file " << "HuffmanCompress_test.htc" << " success!" << endl;

	//将哈夫曼编码有关的配置信息写入文件中
	WriteConfigInfoInFile(fOut, fileName);

	//将字符编码写入文件中
	WriteCodeInFile(fIn, fOut);

	//关闭文件
	fclose(fIn);
	fclose(fOut);

	cout << "HuffmanCompress success !" << endl;
}

void HuffmanCompress::UnCompress()
{
/*
哈夫曼解压缩思路：
1，读取文件名，创建文件（思考：相对路径/绝对路径）
2，根据有效字符个数，以及字符和字符出现次数，创建哈夫曼树
3，根据压缩文件的二进制01序列，遍历哈夫曼树，进行解码
*/

	FILE* fIn = fopen("HuffmanCompress_test.htc", "r");
	if (nullptr == fIn)
	{
		cout << "Open file " << "HuffmanCompress_test.htc" << " error!" << endl;
		return;
	}
	else
		cout << "Open file " << "HuffmanCompress_test.htc" << " success!" << endl;

	//1，获取文件名
	string fileName;
	char ch = 0;
	while ('\n' != (ch = fgetc(fIn)))
		fileName += ch;
	fileName += ".uhtc";

	//2，根据有效字符个数，以及字符和字符出现次数，创建哈夫曼树
	//获取有效字符个数
	size_t effectCount = 0;//有效字符个数
	string strEffectCount;//保存文件中表示有效字符的字符串
	while ('\n' != (ch = fgetc(fIn)))
		strEffectCount += ch;
	effectCount = atoi(strEffectCount.c_str());
	
	//获取字符以及它们各自个数，还有总的有效字符个数（因为压缩时，不满足8位的后面补上0）
	size_t TotalCount = 0;
	while (effectCount)
	{
		char curCh = fgetc(fIn);//获取当前字符
		fgetc(fIn);//获取逗号
		size_t count = 0;//该字符出现次数
		string chCount;//保存文件中表示字符出现个数的字符串
		char ch = 0;
		while ('\n' != (ch = fgetc(fIn)))//获取字符出现个数
			chCount += ch;
		count = atoi(chCount.c_str());
		_FileInfo[curCh]._count = count;

		TotalCount += count;
		--effectCount;
	}


	//构建哈夫曼树
	HuffmanTree<CharInfo> ht(_FileInfo, 256, CharInfo(0));
	cout << "构建哈夫曼树成功" << endl;

	//3，根据压缩文件的二进制01序列，遍历哈夫曼树，进行解码
	//打开将要写入内容的文件
	FILE* fOut = fopen(fileName.c_str(), "w");
	if (nullptr == fOut)
	{
		cout << "Open file " << fileName.c_str() << " error!" << endl;
		return;
	}
	else
		cout << "Open file " << fileName.c_str() << " success!" << endl;

	char* readBuff = new char[1024];//一次最多读取1024个字节（提高读写效率）
	char* writeBuff = new char[1024];//一次对多写入1024个字节
	size_t writeSize = 0;//写入缓冲区writeBuff中字节个数

	HuffmanTreeNode<CharInfo>* pCur = ht.GetRoot();//指向当前树中的位置
	while (true)
	{
		size_t readSize = fread(readBuff, 1, 1024, fIn);

		if (readSize)
		{
			for (size_t i = 0; i < readSize; ++i)
			{
				char ch = readBuff[i];
				//从readBuff缓冲区中读取一个字符
				for (int pos = 7; pos >= 0; --pos)//pos表示当前字符中需要使用的比特位（0-7）
				{
					if ((ch >> pos) & 1)//ch的pos位是1
						pCur = pCur->_pRight;//往右子树递进
					else//ch的pos位是0
						pCur = pCur->_pLeft;//往左子树递进

					if ((nullptr == pCur->_pLeft) && (nullptr == pCur->_pRight))//判断是否到达某个叶子结点
					{
						writeBuff[writeSize] = pCur->_weight._ch;//将叶子结点的值表示的字符写入缓冲区中
						++writeSize;

						if (1024 == writeSize)//writeBuff缓冲区写满了
						{
							fwrite(writeBuff, 1, 1024, fOut);
							writeSize = 0;//缓冲区清空，重新开始写入
						}

						pCur = ht.GetRoot();//重新从根结点开始根据01序列遍历树

						if (0 == --TotalCount)//写入个数，超过最大有效字符个数，退出。由于最多只有7个比特是补充的，
							break;//所以最多只会超出7个字符，由于readBuff一次读取1024个字节，所以，下次循环必定跳出）
					}
				}
			}
		}
		else
			break;

		if (writeSize)//writeBuff缓冲区中还有数据，没有写入文件中
			fwrite(writeBuff, 1, writeSize, fOut);
	}

	//释放缓冲区
	delete[] readBuff;
	delete[] writeBuff;

	//关闭文件
	fclose(fIn);
	fclose(fOut);

}

//统计文件中各个字符出现次数
void HuffmanCompress::GetEachCharCount(FILE*& fIn)
{
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

	//释放缓冲区
	delete[] pReadBuff;
}

//保存各个字符的哈夫曼编码
void HuffmanCompress::GeneratorHuffmanCode(HuffmanTreeNode<CharInfo>* pRoot, string& strCode)
{	//利用先序遍历的思想
	if (nullptr == pRoot)
		return;
	
	if (nullptr == pRoot->_pLeft && nullptr == pRoot->_pRight)
		_FileInfo[pRoot->_weight._ch]._strCode = strCode;

	GeneratorHuffmanCode(pRoot->_pLeft, strCode + '0');//传递一个临时变量的引用（左子树为0）

	GeneratorHuffmanCode(pRoot->_pRight, strCode + '1');//传递一个临时变量的引用（右子树为1）
}

//将编码配置信息写入文件中
void HuffmanCompress::WriteConfigInfoInFile(FILE*& fOut, const string& fileName)
{
/*
1，文件后缀名（如：.txt，然后换行）
2，有效字符个数（如：4，然后换行）
3，各个有效字符出现次数（例如：B，3不同字符以换行结束）
*/
	string strConfig;//保存配置信息

	//将文件名写入配置信息
	strConfig += (fileName+'\n');

	string strCount;//保存：每个字符以及他们出现个数（字符及个数以逗号分开）（不同字符以换行符隔开）
	size_t effectCount = 0;//有效字符个数
	for (size_t i = 0; i < 256; ++i)
	{
	
		if (_FileInfo[i]._count)
		{
			//保存字符及其出现次数
			strCount += _FileInfo[i]._ch;
			strCount += ',';//字符以及出现次数以逗号分开
			char charCount[10] = { 0 };
			strCount += _itoa(_FileInfo[i]._count, charCount, 10);
			strCount += '\n';//不同字符以换行符分开

			++effectCount;
		}
	}

	//将有效字符写入配置信息中
	char numberBuff[3] = {0};
	strConfig += _itoa(effectCount, numberBuff, 10);
	strConfig += '\n';

	//将每个字符以及出现次数写入配置信息
	strConfig += strCount;
	
	//将编码配置信息写入文件中
	size_t size = strConfig.length();
	for (size_t i = 0; i < size; ++i)
		fputc(strConfig[i], fOut);
}

//将字符编码写入文件中
void HuffmanCompress::WriteCodeInFile(FILE*& fIn, FILE*& fOut)
{
	char* pReadBuff = new char[1024];//最多一次读取1024个字节（一次读取一个字符，效率低）
	char* pWriteBuff = new char[1024];//写入文件的缓存区。最多一次写入1024（一次写入一个字符，效率低）
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
}

#endif //_HUFFMANCOMPRESS_H_

