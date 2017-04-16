/*
功能：创建一个迷宫类，存储来文件的内容，来进行相关操作。
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
	void display();//打印迷宫
	bool pass_maze(int row, int col);//走迷宫
	~Maze();
private:	
//	void WriteFile(const char* fileName);//写入文件内容
	void ReadFile(const char* fileName);//读取文件内容
	bool isPath(int row, int col);//判断该点是否是路
private:
	char* m_ptr;//指向一个二维数组
	int m_row;//迷宫行数
	int m_col; //迷宫列数
	int start;//进行第一次走的判断，为1则不能往回走。
};

#endif //_MAZE_H_
