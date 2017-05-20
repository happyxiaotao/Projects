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
	char _ch;
	long _count;
	string _strCode;
};

/*
��֪�������⣺
1��ѹ�����˺���
2�����ļ��ַ�����ʱ������������һЩ�ַ�
3�����ļ�ֻ��һ���ַ�ʱ����ѹ���ˣ�ѹ���ļ�Ϊ�գ�
*/
class HuffmanCompress
{
public:
	HuffmanCompress(const string& fileName);//������ѹ��
	void UnCompress();//��������ѹ��
private:
	//ͳ���ļ����ַ����ִ���
	void GetEachCharCount(FILE*& fIn);
	//��������ַ��Ĺ���������
	void GeneratorHuffmanCode(HuffmanTreeNode<CharInfo>* pRoot, string& strCode);
	//���ļ���д��һЩ������Ϣ
	void WriteConfigInfoInFile(FILE*& fOut, const string& fileName);
	//���ַ�����д���ļ�
	void WriteCodeInFile(FILE*& fIn, FILE*& fOut);
private:
	CharInfo _FileInfo[256];//һ����256�в�ͬ���ַ����������������ַ���ɵģ�
};

HuffmanCompress::HuffmanCompress(const string& fileName)
{/*
	�������ļ�ѹ��˼·��
	1�������ļ���ͳ��256���ַ����ִ���
	2�������ַ�������ִ���������������
	3�����ù��������ҵ�ÿ���ַ��ı���
	4�����¶��ļ����б���
*/

	//�򿪽�Ҫ��ȡ���ݵ��ļ�
	FILE* fIn = fopen(fileName.c_str(), "r");
	if (nullptr == fIn)
	{
		cout << "Open file " << fileName << " error!" << endl;
		return;
	}
	else
		cout << "Open file " << fileName << " success!" << endl;

	//1����ȡ�����ַ����ִ���
	GetEachCharCount(fIn);

	//2��������������
	HuffmanTree<CharInfo> ht(_FileInfo, 256, CharInfo(0));

	//3����������ַ��Ĺ���������
	string strCode;
	HuffmanTreeNode<CharInfo>* pRoot = ht.GetRoot();
	GeneratorHuffmanCode(pRoot, strCode);//���ɸ����ַ��ı���

	//4�������������ļ��������±���
	fseek(fIn, 0, SEEK_SET);//���ظղŴ��ļ���ͷ��

	//�򿪽�Ҫд�����ݵ��ļ�
	FILE* fOut = fopen("HuffmanCompress_test.htc", "w");
	if (nullptr == fOut)
	{
		cout << "Open file " << "HuffmanCompress_test.htc" << " error!" << endl;
		return;
	}
	else
		cout << "Open file " << "HuffmanCompress_test.htc" << " success!" << endl;

	//�������������йص�������Ϣд���ļ���
	WriteConfigInfoInFile(fOut, fileName);

	//���ַ�����д���ļ���
	WriteCodeInFile(fIn, fOut);

	//�ر��ļ�
	fclose(fIn);
	fclose(fOut);

	cout << "HuffmanCompress success !" << endl;
}

void HuffmanCompress::UnCompress()
{
/*
��������ѹ��˼·��
1����ȡ�ļ����������ļ���˼�������·��/����·����
2��������Ч�ַ��������Լ��ַ����ַ����ִ�����������������
3������ѹ���ļ��Ķ�����01���У������������������н���
*/

	FILE* fIn = fopen("HuffmanCompress_test.htc", "r");
	if (nullptr == fIn)
	{
		cout << "Open file " << "HuffmanCompress_test.htc" << " error!" << endl;
		return;
	}
	else
		cout << "Open file " << "HuffmanCompress_test.htc" << " success!" << endl;

	//1����ȡ�ļ���
	string fileName;
	char ch = 0;
	while ('\n' != (ch = fgetc(fIn)))
		fileName += ch;
	fileName += ".uhtc";

	//2��������Ч�ַ��������Լ��ַ����ַ����ִ�����������������
	//��ȡ��Ч�ַ�����
	size_t effectCount = 0;//��Ч�ַ�����
	string strEffectCount;//�����ļ��б�ʾ��Ч�ַ����ַ���
	while ('\n' != (ch = fgetc(fIn)))
		strEffectCount += ch;
	effectCount = atoi(strEffectCount.c_str());
	
	//��ȡ�ַ��Լ����Ǹ��Ը����������ܵ���Ч�ַ���������Ϊѹ��ʱ��������8λ�ĺ��油��0��
	size_t effectCountTemp = effectCount;
	size_t TotalCount = 0;
	char curCh = 0;//���һ�λ�ȡ����Ч�ַ�
	while (effectCountTemp)
	{
		curCh = fgetc(fIn);//��ȡ��ǰ�ַ�
		fgetc(fIn);//��ȡ����
		size_t count = 0;//���ַ����ִ���
		string chCount;//�����ļ��б�ʾ�ַ����ָ������ַ���
		char ch = 0;
		while ('\n' != (ch = fgetc(fIn)))//��ȡ�ַ����ָ���
			chCount += ch;
		count = atoi(chCount.c_str());
		_FileInfo[curCh]._count = count;

		TotalCount += count;
		--effectCountTemp;
	}


	//������������
	HuffmanTree<CharInfo> ht(_FileInfo, 256, CharInfo(0));
	cout << "�������������ɹ�" << endl;

	//3������ѹ���ļ��Ķ�����01���У������������������н���
	//�򿪽�Ҫд�����ݵ��ļ�
	FILE* fOut = fopen(fileName.c_str(), "w");
	if (nullptr == fOut)
	{
		cout << "Open file " << fileName.c_str() << " error!" << endl;
		return;
	}
	else
		cout << "Open file " << fileName.c_str() << " success!" << endl;



	char* readBuff = new char[1024];//һ������ȡ1024���ֽڣ���߶�дЧ�ʣ�
	char* writeBuff = new char[1024];//һ�ζԶ�д��1024���ֽ�
	size_t writeSize = 0;//д�뻺����writeBuff���ֽڸ���

	//���ļ���ֻ��һ���ַ�ʱ
	if (1 == effectCount)
	{
		size_t TotalCountTemp = TotalCount;
		while (true)
		{
			if (TotalCountTemp > 1024)
			{
				for (int i = 0; i < 1024; ++i)
					writeBuff[i] = curCh;
				fwrite(writeBuff, 1, 1024, fOut);
				TotalCountTemp -= 1024;
			}
			else
			{
				for (int i = 0; i < TotalCountTemp; ++i)
					writeBuff[i] = curCh;
				fwrite(writeBuff, 1, TotalCountTemp, fOut);
				break;
			}
		}

		delete[] writeBuff;
		delete[] readBuff;
		fclose(fIn);
		fclose(fOut);
		return;
	}

	HuffmanTreeNode<CharInfo>* pCur = ht.GetRoot();//ָ��ǰ���е�λ��
	while (true)
	{
		size_t readSize = fread(readBuff, 1, 1024, fIn);

		if (readSize)
		{
			for (size_t i = 0; i < readSize; ++i)
			{
				char ch = readBuff[i];
				//��readBuff�������ж�ȡһ���ַ�
				for (int pos = 7; pos >= 0; --pos)//pos��ʾ��ǰ�ַ�����Ҫʹ�õı���λ��0-7��
				{
					if ((ch >> pos) & 1)//ch��posλ��1
						pCur = pCur->_pRight;//���������ݽ�
					else//ch��posλ��0
						pCur = pCur->_pLeft;//���������ݽ�

					if ((nullptr == pCur->_pLeft) && (nullptr == pCur->_pRight))//�ж��Ƿ񵽴�ĳ��Ҷ�ӽ��
					{
						writeBuff[writeSize] = pCur->_weight._ch;//��Ҷ�ӽ���ֵ��ʾ���ַ�д�뻺������
						++writeSize;

						if (1024 == writeSize)//writeBuff������д����
						{
							fwrite(writeBuff, 1, 1024, fOut);
							writeSize = 0;//��������գ����¿�ʼд��
						}

						pCur = ht.GetRoot();//���´Ӹ���㿪ʼ����01���б�����

						if (0 == --TotalCount)//д����������������Ч�ַ��������˳����������ֻ��7�������ǲ���ģ�
							break;//�������ֻ�ᳬ��7���ַ�������readBuffһ�ζ�ȡ1024���ֽڣ����ԣ��´�ѭ���ض�������
					}
				}
			}
		}
		else
			break;
	}

	if (writeSize)//writeBuff�������л������ݣ�û��д���ļ���
		fwrite(writeBuff, 1, writeSize, fOut);

	//�ͷŻ�����
	delete[] readBuff;
	delete[] writeBuff;

	//�ر��ļ�
	fclose(fIn);
	fclose(fOut);

}

//ͳ���ļ��и����ַ����ִ���
void HuffmanCompress::GetEachCharCount(FILE*& fIn)
{
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

	//�ͷŻ�����
	delete[] pReadBuff;
}

//��������ַ��Ĺ���������
void HuffmanCompress::GeneratorHuffmanCode(HuffmanTreeNode<CharInfo>* pRoot, string& strCode)
{	//�������������˼��
	if (nullptr == pRoot)
		return;
	
	if (nullptr == pRoot->_pLeft && nullptr == pRoot->_pRight)
		_FileInfo[pRoot->_weight._ch]._strCode = strCode;

	GeneratorHuffmanCode(pRoot->_pLeft, strCode + '0');//����һ����ʱ���������ã�������Ϊ0��

	GeneratorHuffmanCode(pRoot->_pRight, strCode + '1');//����һ����ʱ���������ã�������Ϊ1��
}

//������������Ϣд���ļ���
void HuffmanCompress::WriteConfigInfoInFile(FILE*& fOut, const string& fileName)
{
/*
1���ļ���׺�����磺.txt��Ȼ���У�
2����Ч�ַ��������磺4��Ȼ���У�
3��������Ч�ַ����ִ��������磺B��3��ͬ�ַ��Ի��н�����
*/
	string strConfig;//����������Ϣ

	//���ļ���д��������Ϣ
	strConfig += (fileName+'\n');

	string strCount;//���棺ÿ���ַ��Լ����ǳ��ָ������ַ��������Զ��ŷֿ�������ͬ�ַ��Ի��з�������
	size_t effectCount = 0;//��Ч�ַ�����
	for (size_t i = 0; i < 256; ++i)
	{
	
		if (_FileInfo[i]._count)
		{
			//�����ַ�������ִ���
			strCount += _FileInfo[i]._ch;
			strCount += ',';//�ַ��Լ����ִ����Զ��ŷֿ�
			char charCount[10] = { 0 };
			strCount += _itoa(_FileInfo[i]._count, charCount, 10);
			strCount += '\n';//��ͬ�ַ��Ի��з��ֿ�

			++effectCount;
		}
	}

	//����Ч�ַ�д��������Ϣ��
	char numberBuff[3] = {0};
	strConfig += _itoa(effectCount, numberBuff, 10);
	strConfig += '\n';

	//��ÿ���ַ��Լ����ִ���д��������Ϣ
	strConfig += strCount;
	
	//������������Ϣд���ļ���
	size_t size = strConfig.length();
	for (size_t i = 0; i < size; ++i)
		fputc(strConfig[i], fOut);
}

//���ַ�����д���ļ���
void HuffmanCompress::WriteCodeInFile(FILE*& fIn, FILE*& fOut)
{
	char* pReadBuff = new char[1024];//���һ�ζ�ȡ1024���ֽڣ�һ�ζ�ȡһ���ַ���Ч�ʵͣ�
	char* pWriteBuff = new char[1024];//д���ļ��Ļ����������һ��д��1024��һ��д��һ���ַ���Ч�ʵͣ�
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
}

#endif //_HUFFMANCOMPRESS_H_

