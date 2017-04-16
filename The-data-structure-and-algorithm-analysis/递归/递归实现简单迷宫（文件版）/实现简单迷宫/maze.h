/*
���ܣ�����һ���Թ��࣬�洢���ļ������ݣ���������ز�����
*/
#pragma once

#ifndef _MAZE_H_
#define _MAZE_H_

#include <iostream>
#include <fstream>
using namespace std;

class Maze
{
public:	
	Maze(const char* fileName);
	void display();//��ӡ�Թ�
	bool pass_maze(int row, int col);//���Թ�
	~Maze();
private:	
//	void WriteFile(const char* fileName);//д���ļ�����
	void ReadFile(const char* fileName);//��ȡ�ļ�����
	bool isPath(int row, int col);//�жϸõ��Ƿ���·
private:
	char* m_ptr;//ָ��һ����ά����
	int m_row;//�Թ�����
	int m_col; //�Թ�����
	int start;//���е�һ���ߵ��жϣ�Ϊ1���������ߡ�
};

#endif //_MAZE_H_
