#include "maze.h"

Maze::Maze(const char* fileName):m_ptr(nullptr),m_row(0),m_col(0)
{
	ReadFile(fileName);
	//start=1��ʾ��һ���ߣ�ͨ���ж�start�Ƿ�Ϊ1�������Ƿ������ߡ�
	start = 1;
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

	for (int i = 0; i < m_row; ++i)
	{
		for (int j = 0; j < m_col; ++j)
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
	for (int i = 0; i < m_row; ++i)
	{
		for (int j = 0; j < m_col; ++j)
			cout << static_cast<int>(m_ptr[i*m_col+j]) << ' ';
		cout << endl;
	}
}

//�ж��Ƿ���·
bool Maze::isPath(int row, int col)
{
	return 1 == m_ptr[row*m_col+col];
}

//�ݹ�˼�룺
//��ǰ������ͨ��ǰ���Ǹõ�����ܵ�������ͨ��
//���ݹ飬�����ݹ���ڣ����ɡ�ע���߹��ĵ㣬ֵ��Ϊ2������߹���
bool Maze::pass_maze(int row, int col)
{
//��Ϊ���õݹ飬���������������Զ����ص���һ���ĵص�
	if ((row < 0 || row >= m_row) || (col < 0) || col >= m_col)
		return true;
	
	if (isPath(row, col))
		m_ptr[row*m_col+col] = 2;
	else
		return false;

	//��һ�ν���ʱ�����������ߣ�
	if (start == 1)
	{
		start++;
	}
	else
	{
		//����
		if (pass_maze(row + 1, col))
			return true;
	}
	//����
	if (pass_maze(row - 1, col))
		return true;

	//����
	if (pass_maze(row, col + 1))
		return true;
	//����
	if (pass_maze(row, col - 1))
		return true;

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
