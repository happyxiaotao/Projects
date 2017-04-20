/*
�ݹ���������Թ����޳������⣨�ļ��棩
*/

#include "maze.h"
#include "createFile.hpp"

void play(const char* fileName)
{
	Maze maze(fileName);

	cout << "�Թ���ͼ��0����ǽ��1����·��" << endl;
	maze.display();

	//ȱ�ݣ�ÿһ�ؿ��������ͬ(���Խ������Ϣ���뵽�ļ���)
	if (maze.pass_maze(9, 6))
		cout << "�Թ��г���" << endl;
	else
		cout << "�Թ��޳���" << endl;

	cout << endl;
}
void game(int choose)
{
	//ѡ��ͬ�Ĺؿ��ļ���
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
	//�������йؿ��ļ�
	loadFile();

	//ѡ��ؿ�
	int choose = 0;
	do
	{
		cout << "ѡ����һ��" << endl;
		cout << "1���ؿ�1" << endl;
		cout << "2���ؿ�2" << endl;
		cout << "3���ؿ�3" << endl;
		cout << "0���˳�" << endl;
		cout << "���룺";
		cin >> choose;
		game(choose);
	} while (1);

	system("pause");
	return 0;
}