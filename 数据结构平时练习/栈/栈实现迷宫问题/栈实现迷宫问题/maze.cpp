#include "maze.h"

Maze::Maze(const char* fileName) :m_ptr(nullptr), m_row(0), m_col(0)
{
	ReadFile(fileName);
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

	for (size_t i = 0; i < m_row; ++i)
	{
		for (size_t j = 0; j < m_col; ++j)
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
	for (size_t i = 0; i < m_row; ++i)
	{
		for (size_t j = 0; j < m_col; ++j)
			cout << static_cast<int>(m_ptr[i*m_col + j]) << ' ';
		cout << endl;
	}
}

//判断是否是路
bool Maze::isPath(int row, int col)
{
	return 1 == m_ptr[row*m_col + col];
}

/*利用栈的思想
1,将入口点放入栈中，然后沿入口点四周某一个表示路的点放入栈中，作为下次的入口(并标记该点走过)，按某一顺序进栈。
2,若某一阶段，放入的点是出口。则表示有路。
3,若某一阶段，该点的四周没有可以继续放入的点，则该点出栈。将当前栈顶元素作为入口，进行1步,寻找其他出口。
4，若最后栈为空，则表示没有出口。
*/
//判读迷宫是否有出口
bool Maze::pass_maze(int row, int col)
{
	stack<Seat> s;
	s.push(Seat(row, col));//将入口入栈

	while (!s.empty())//当栈不为空时
	{
		Seat& cur = s.top();

		//若该点是边界点且不是入口点，则为出口点。
		if ((cur.m_row == 0 || cur.m_row == m_row-1) || (cur.m_col == 0) || cur.m_col == m_col-1)
			if(1 != s.size())//当只有一个元素时，表示入口点。
				return true;

		if ((1 != s.size()) && (isPath(cur.m_row + 1, cur.m_col)))//不是从初始点入口往下走，向下
			s.push(Seat(cur.m_row + 1, cur.m_col));
		else if (isPath(cur.m_row - 1, cur.m_col))//向上
			s.push(Seat(cur.m_row - 1, cur.m_col));
		else if (isPath(cur.m_row, cur.m_col + 1))//向左
			s.push(Seat(cur.m_row, cur.m_col + 1));
		else if (isPath(cur.m_row, cur.m_col - 1))//向右
			s.push(Seat(cur.m_row, cur.m_col - 1));
		else
			s.pop();//周围没有可以走的点，该点出栈。

		m_ptr[cur.m_row*m_col + cur.m_col] = 2;//置为2，表示当前点已经走过
	}

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
