#pragma once
#ifndef _MAZE_H_
#define _MAZE_H_
#include <iostream>
#include <fstream>
#include <stack>
using namespace std;

//�洢�����Ϣ
class Seat
{
public:
	Seat(size_t row, size_t col) :m_row(row), m_col(col) 
	{}
public:
	int m_row;
	int m_col;
};

class Maze
{
public:
	Maze(const char* fileName);//���캯������Ϊ������ļ���
	void display();//��ӡ�Թ�
	bool pass_maze(int row, int col);//���Թ�
	~Maze();
private:
	//	void WriteFile(const char* fileName);//д���ļ�����
	void ReadFile(const char* fileName);//��ȡ�ļ�����
	bool isPath(int row, int col);//�жϸõ��Ƿ���·
private:
	char* m_ptr;//ָ��һ����ά����
	size_t m_row;//�Թ�����
	size_t m_col; //�Թ�����
};

#endif //_MAZE_H_