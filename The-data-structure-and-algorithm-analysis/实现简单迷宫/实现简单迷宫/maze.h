//#pragma once
//
//#ifndef _MAZE_H_
//#define _MAZE_H_
//
//#include <iostream>
//using namespace std;
//
//const int MAX_ROW = 10;
//const int MAX_COL = 10;
//
//char mapArr[MAX_ROW][MAX_COL] = {
//	{ 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 },
//	{ 0, 0, 1, 1, 1, 0, 0, 0, 0, 0 },
//	{ 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 },
//	{ 1, 0, 0, 0, 1, 0, 0, 0, 0, 0 },
//	{ 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 },
//	{ 0, 0, 1, 1, 1, 0, 0, 0, 0, 0 },
//	{ 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 },
//	{ 0, 0, 1, 1, 0, 0, 0, 0, 0, 0 },
//	{ 0, 0, 0, 1, 1, 1, 1, 0, 0, 0 },
//	{ 0, 0, 0, 0, 0, 0, 1, 0, 0, 0 } };
//
//class Maze
//{
//public:
//	Maze(char** map_ptr = nullptr, int row = MAX_ROW, int col = MAX_COL);
//	void display();
//	bool pass_maze();
//	~Maze();
//private:
//	bool isPath(int row, int col);
//public:
//	char** m_ptr;
//	int m_row;
//	int m_col;
//};
//
//#endif //_MAZE_H_
