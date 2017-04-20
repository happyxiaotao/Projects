#pragma once
#ifndef _MAZE_H_
#define _MAZE_H_
#include <iostream>
#include <fstream>
#include <stack>
using namespace std;

//存储点的信息
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
	Maze(const char* fileName);//构造函数参数为载入的文件名
	void display();//打印迷宫
	bool pass_maze(int row, int col);//走迷宫
	~Maze();
private:
	//	void WriteFile(const char* fileName);//写入文件内容
	void ReadFile(const char* fileName);//读取文件内容
	bool isPath(int row, int col);//判断该点是否是路
private:
	char* m_ptr;//指向一个二维数组
	size_t m_row;//迷宫行数
	size_t m_col; //迷宫列数
};

#endif //_MAZE_H_