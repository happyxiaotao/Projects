/*
�Թ�����

�Ƽ���ַ��http://c.biancheng.net/cpp/biancheng/view/259.html
*/
//#include "maze.h"
#include <iostream>
using namespace std;

static int START = 1;
const int MAX_ROW = 10;
const int MAX_COL = 10;

char mapArr[MAX_ROW][MAX_COL] = {
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 1, 1, 1, 1, 1, 1, 1, 0, 0 },
	{ 0, 1, 0, 0, 1, 0, 0, 1, 0, 0 },
	{ 0, 1, 0, 0, 1, 0, 0, 1, 0, 0 },
	{ 0, 1, 0, 0, 1, 0, 0, 1, 0, 0 },
	{ 0, 1, 1, 1, 1, 0, 0, 1, 0, 0 },
	{ 0, 0, 1, 0, 1, 0, 0, 1, 0, 0 },
	{ 0, 0, 1, 1, 1, 0, 0, 1, 1, 0 },
	{ 0, 0, 0, 1, 1, 1, 1, 0, 1, 1 },
	{ 0, 0, 0, 0, 0, 0, 1, 0, 0, 0 } };

bool isPath(char (*maze_ptr)[10], int row, int col)
{
	return 1 == maze_ptr[row][col];
}
void display(char(*maze_ptr)[10], int row, int col)
{
	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < col; ++j)
			cout << static_cast<int>(mapArr[i][j]) << ' ';
		cout << endl;
	}
}
bool pass_maze(char (*maze_ptr)[10], int row, int col)
{
//��Ϊ���õݹ飬���������������Զ����ص���һ���ĵص�
	if ((row < 0 || row >= MAX_ROW) || (col < 0) || col >= MAX_COL)
		return true;
	
	if (isPath(maze_ptr, row, col))
		maze_ptr[row][col] = 2;
	else
		return false;

	//��һ�ν���ʱ�����������ߣ�
	if (START == 1)
	{
		START++;
	}
	else
	{
		//����
		if (pass_maze(maze_ptr, row + 1, col))
			return true;
	}
	//����
	if (pass_maze(maze_ptr, row - 1, col))
		return true;

	//����
	if (pass_maze(maze_ptr, row, col + 1))
		return true;
	//����
	if (pass_maze(maze_ptr, row, col - 1))
		return true;


	return false;
}

int main()
{
	display(mapArr, MAX_ROW, MAX_COL);
	
	cout << endl << pass_maze(mapArr, 9, 6) << endl;

	display(mapArr, MAX_ROW, MAX_COL);
	system("pause");

	return 0;
}