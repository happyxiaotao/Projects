#include "maze.h"

Maze::Maze(const char* fileName) :m_ptr(nullptr), m_row(0), m_col(0)
{
	ReadFile(fileName);
}

//���ļ�������
void Maze::ReadFile(const char* fileName)
{
	//���ļ�
	ifstream ifs(fileName, ifstream::in);
	if (!ifs)
	{
		cerr << "read" << fileName << "error!" << endl;
		exit(2);
	}
	//һ���ַ�һ���ַ���ȡ�ļ�
	char c;

	//��ȡ����
	ifs.get(c);
	m_row = static_cast<int>(c);
	//��ȡ����
	ifs.get(c);
	m_col = static_cast<int>(c);
	//�����з���ȡ
	ifs.get(c);

	//��̬���ٿռ�
	m_ptr = new char[m_row*m_col];

	for (size_t i = 0; i < m_row; ++i)
	{
		for (size_t j = 0; j < m_col; ++j)
		{
			ifs.get(c);
			m_ptr[i*m_col + j] = c;
		}
		//��ȡ���з�
		ifs.get(c);
	}
	//�ر��ļ�
	ifs.close();
}

//��ӡ��ͼ
void Maze::display()
{
	for (size_t i = 0; i < m_row; ++i)
	{
		for (size_t j = 0; j < m_col; ++j)
			cout << static_cast<int>(m_ptr[i*m_col + j]) << ' ';
		cout << endl;
	}
}

//�ж��Ƿ���·
bool Maze::isPath(int row, int col)
{
	return 1 == m_ptr[row*m_col + col];
}

/*����ջ��˼��
1,����ڵ����ջ�У�Ȼ������ڵ�����ĳһ����ʾ·�ĵ����ջ�У���Ϊ�´ε����(����Ǹõ��߹�)����ĳһ˳���ջ��
2,��ĳһ�׶Σ�����ĵ��ǳ��ڡ����ʾ��·��
3,��ĳһ�׶Σ��õ������û�п��Լ�������ĵ㣬��õ��ջ������ǰջ��Ԫ����Ϊ��ڣ�����1��,Ѱ���������ڡ�
4�������ջΪ�գ����ʾû�г��ڡ�
*/
//�ж��Թ��Ƿ��г���
bool Maze::pass_maze(int row, int col)
{
	stack<Seat> s;
	s.push(Seat(row, col));//�������ջ

	while (!s.empty())//��ջ��Ϊ��ʱ
	{
		Seat& cur = s.top();

		//���õ��Ǳ߽���Ҳ�����ڵ㣬��Ϊ���ڵ㡣
		if ((cur.m_row == 0 || cur.m_row == m_row-1) || (cur.m_col == 0) || cur.m_col == m_col-1)
			if(1 != s.size())//��ֻ��һ��Ԫ��ʱ����ʾ��ڵ㡣
				return true;

		if ((1 != s.size()) && (isPath(cur.m_row + 1, cur.m_col)))//���Ǵӳ�ʼ����������ߣ�����
			s.push(Seat(cur.m_row + 1, cur.m_col));
		else if (isPath(cur.m_row - 1, cur.m_col))//����
			s.push(Seat(cur.m_row - 1, cur.m_col));
		else if (isPath(cur.m_row, cur.m_col + 1))//����
			s.push(Seat(cur.m_row, cur.m_col + 1));
		else if (isPath(cur.m_row, cur.m_col - 1))//����
			s.push(Seat(cur.m_row, cur.m_col - 1));
		else
			s.pop();//��Χû�п����ߵĵ㣬�õ��ջ��

		m_ptr[cur.m_row*m_col + cur.m_col] = 2;//��Ϊ2����ʾ��ǰ���Ѿ��߹�
	}

	//û��ͨ·������false
	return false;
}

Maze::~Maze()
{
	if (m_ptr)
	{
		delete[] m_ptr;
		m_ptr = nullptr;//��ϰ��
	}
}
