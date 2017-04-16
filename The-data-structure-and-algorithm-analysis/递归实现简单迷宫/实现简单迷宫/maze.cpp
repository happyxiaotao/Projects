#include "maze.h"

Maze::Maze(const char* fileName):m_ptr(nullptr),m_row(0),m_col(0)
{
	ReadFile(fileName);
	//start=1表示第一次走，通过判断start是否为1，决定是否往回走。
	start = 1;
}

//从文件读内容
void Maze::ReadFile(const char* fileName)
{
	//打开文件
	ifstream ifs(fileName, ifstream::in);
	if (!ifs)
	{
		cerr << "read" << fileName << "error!" << endl;
		exit(2);
	}
	//一个字符一个字符读取文件
	char c;

	//读取行数
	ifs.get(c);
	m_row = static_cast<int>(c);
	//读取列数
	ifs.get(c);
	m_col = static_cast<int>(c);
	//将换行符读取
	ifs.get(c);

	//动态开辟空间
	m_ptr = new char[m_row*m_col];

	for (int i = 0; i < m_row; ++i)
	{
		for (int j = 0; j < m_col; ++j)
		{
			ifs.get(c);
			m_ptr[i*m_col + j] = c;
		}
		//读取换行符
		ifs.get(c);
	}
	//关闭文件
	ifs.close();
}

//打印地图
void Maze::display()
{
	for (int i = 0; i < m_row; ++i)
	{
		for (int j = 0; j < m_col; ++j)
			cout << static_cast<int>(m_ptr[i*m_col+j]) << ' ';
		cout << endl;
	}
}

//判断是否是路
bool Maze::isPath(int row, int col)
{
	return 1 == m_ptr[row*m_col+col];
}

//递归思想：
//当前点能走通的前提是该点的四周点能耐走通，
//层层递归，给出递归出口，即可。注意走过的点，值置为2（标记走过）
bool Maze::pass_maze(int row, int col)
{
//因为利用递归，当不满足条件后，自动返回到上一步的地点
	if ((row < 0 || row >= m_row) || (col < 0) || col >= m_col)
		return true;
	
	if (isPath(row, col))
		m_ptr[row*m_col+col] = 2;
	else
		return false;

	//第一次进入时，不能往回走，
	if (start == 1)
	{
		start++;
	}
	else
	{
		//向下
		if (pass_maze(row + 1, col))
			return true;
	}
	//向上
	if (pass_maze(row - 1, col))
		return true;

	//向左
	if (pass_maze(row, col + 1))
		return true;
	//向右
	if (pass_maze(row, col - 1))
		return true;

	//没有通路，返回false
	return false;
}

Maze::~Maze()
{
	if (m_ptr)
	{
		delete[] m_ptr;
		m_ptr = nullptr;//好习惯
	}
}
