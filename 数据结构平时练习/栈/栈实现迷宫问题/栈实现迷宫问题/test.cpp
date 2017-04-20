/*
递归问题求解迷宫有无出口问题（文件版）
*/

#include "maze.h"
#include "createFile.hpp"

void play(const char* fileName)
{
	Maze maze(fileName);

	cout << "迷宫地图（0代表墙，1代表路）" << endl;
	maze.display();

	//缺陷：每一关卡的入口相同(可以将入口信息加入到文件中)
	if (maze.pass_maze(9, 6))
		cout << "迷宫有出口" << endl;
	else
		cout << "迷宫无出口" << endl;

	cout << endl;
}
void game(int choose)
{
	//选择不同的关卡文件。
	char* fileName = nullptr;
	switch (choose)
	{
	case 1:
		fileName = file[0];
		break;
	case 2:
		fileName = file[1];
		break;
	case 3:
		fileName = file[2];
		break;
	case 0:
		exit(0);
	default:
		break;
	}

	play(fileName);
}

int main()
{
	//载入所有关卡文件
	loadFile();

	//选择关卡
	int choose = 0;
	do
	{
		cout << "选择下一步" << endl;
		cout << "1：关卡1" << endl;
		cout << "2：关卡2" << endl;
		cout << "3：关卡3" << endl;
		cout << "0：退出" << endl;
		cout << "输入：";
		cin >> choose;
		game(choose);
	} while (1);

	system("pause");
	return 0;
}