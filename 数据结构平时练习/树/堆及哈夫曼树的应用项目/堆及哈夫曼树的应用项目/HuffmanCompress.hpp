#pragma once

#define _CRT_SECURE_NO_WARNINGS

#ifndef _HUFFMANCOMPRESS_H_
#define _HUFFMANCOMPRESS_H_

#include "HuffmanTree.hpp"
#include <string>
#include <iostream>
using namespace std;

struct CharInfo//����ÿ���ַ���Ϣ
{
public:
	CharInfo(long count = 0)
		:_count(count)
	{}
public:
	//��Ҫ�ػ��������������㹹����������
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
	HuffmanCompress(string& fileName);//������ѹ��
	void UnCompress();//��������ѹ��
private:
	//ͳ���ļ����ַ����ִ���
	//��������ַ��Ĺ���������
	void GeneratorHuffmanCode(HuffmanTreeNode<CharInfo>* pRoot, string& strCode);
	//���¶��ļ����б���
	//���ļ���д��һЩ������Ϣ
	void GeneratorConfigInfo(FILE* fOut;
private:
	CharInfo _FileInfo[256];//һ����256�в�ͬ���ַ����������������ַ���ɵģ�
};

HuffmanCompress::HuffmanCompress(string& fileName)
{/*
	�������ļ�ѹ��˼·��
	1�������ļ���ͳ��256���ַ����ִ���
	2�������ַ�������ִ���������������
	3�����ù��������ҵ�ÿ���ַ��ı���
	4�����¶��ļ����б���
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
		_FileInfo[i]._ch = i;//��256���ַ��ڵ㸳ֵ

	char* pReadBuff = new char[1024];//���һ�ζ�ȡ1024���ֽڣ�һ�ζ�ȡһ���ַ���Ч�ʵͣ�
	while (true)	//ͳ�Ƹ����ַ����ִ���
	{
		size_t readSize = fread(pReadBuff, 1, 1024, fIn);//readSize����һ�ζ�ȡ��ʵ�ʸ���

		if (0 == readSize)//û�ж�ȡ���ַ�
			break;

		for (size_t i = 0; i < readSize; ++i)
			_FileInfo[pReadBuff[i]]._count++;
	}

	//������������
	HuffmanTree<CharInfo> ht(_FileInfo, 256, CharInfo(0));

	//��������ַ��Ĺ���������
	string strCode;
	HuffmanTreeNode<CharInfo>* pRoot = ht.GetRoot();
	GeneratorHuffmanCode(pRoot, strCode);

	//���ļ��������±���
	fseek(fIn, 0, SEEK_SET);//���ظղŴ��ļ���ͷ��

	FILE* fOut = fopen("test.hfc", "w");
	char* pWriteBuff = new char[1024];//д���ļ��Ļ����������һ��д��1024
	size_t writeCount = 0;//��ʾ1024�ֽڻ����У��Ѿ�������ֽ���������1024�ֽڣ���һ��д���ļ��У�
	char value = 0;//��ʾһ���ֽڣ���������8λ�����Ʊ���
	int pos = 0;//��ʾһ���ֽڰ�λ���Ѿ�ʹ���˼�λ

	while (true)
	{
		size_t readSize = fread(pReadBuff, 1, 1024, fIn);

		if (readSize)
		{
			for (size_t i = 0; i < readSize; ++i)//����readBuff�е�ÿһ���ַ�
			{
				unsigned char ch = pReadBuff[i];//���뻺�����е�һ���ַ�

				string& strCode = _FileInfo[ch]._strCode;//��ǰ�ַ����ڱ��������
				for (size_t i = 0; i < strCode.length(); ++i)
				{
					value <<= 1;//ע�⣬����λ�����жϣ����⣺�����һλ0��ʾ�洢�ı��������ʱ������1����±������
					if (strCode[i] == '1')
						value |= 1;

					if (8 == ++pos)//pos����1�������жϵ�ǰ�ֽ��Ƿ��Ѿ���������������8λ������writeBuff��������д��value
					{
						pWriteBuff[writeCount] = value;
						++writeCount;//�������У��Ѿ��洢���ֽڸ�����1
						pos = 0;//���¿�ʼ���б���
					}
					if (1024 == writeCount)//�жϻ������Ƿ�д����д����д���ļ���
					{
						fwrite(pWriteBuff, 1, 1024, fOut);
						writeCount = 0;//���¿�ʼ����
					}
				}

			}
		}
		else
			break;
	}

	//ע�⣬�����ļ���ȡ�꣬���ǣ���ǰvalue�л���ʣ��λû�������ϣ����߻��л���������1024�ֽڻ�������û��д���ļ���
	if (pos)//pos����0����ʾ������䣬��Ϊ��pos=8ʱ���Ὣpos��λ0
	{
		value <<= (8 - pos);//ʣ����ز���0��д��writeBuff��������
		pWriteBuff[writeCount] = value;
		++writeCount;
	}
	//ע�⣬pos��writeCount���ж���䣬Ҫ�ֿ�д������д��һ���ж���
	if (writeCount)//ͬpos
	{
		fwrite(pWriteBuff, 1, writeCount, fOut);//�ж��٣�д�����
	}

	//�ͷŻ�����
	delete[] pReadBuff;
	delete[] pWriteBuff;

	//�ر��ļ�
	fclose(fIn);
	fclose(fOut);
}

//��������ַ��Ĺ���������
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

