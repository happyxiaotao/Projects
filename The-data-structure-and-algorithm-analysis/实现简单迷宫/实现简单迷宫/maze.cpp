//#include "maze.h"
//
//Maze::Maze(char** map_ptr, int row, int col)
//{
//	if (map_ptr)
//	{
//		m_ptr = new char*[row];
//
//		for (int i = 0; i < col; ++i)
//			m_ptr[i] = new char[col];
//
//		for (int i = 0; i < row; ++i)
//			for (int j = 0; j < col; ++j)
//				m_ptr[i][j] = map_ptr[i][j];
//	}
//	else
//	{
//		m_ptr = nullptr;
//	}
//	m_row = row;
//	m_col = col;
//}
//
//void Maze::display()
//{
//	for (int i = 0; i < m_row; ++i)
//	{
//		for (int j = 0; j < m_col; ++j)
//			cout << (m_ptr[i][j]) << ' ';
//		cout << endl;
//	}
//}
//
//bool Maze::isPath(int row, int col)
//{
//	return 1 == m_ptr[row - 1][col - 1];
//}
////
////bool pass_maze(char** maze, int row, int col)
////{
////	if ((row < 0 || row >= MAX_ROW) || (col < 0) || col >= MAX_COL)
////		return true;
////	if (!isPath(maze, row, col))
////	{
////		return false;
////	}
////
////	//向左
////	if (isPath(maze, row + 1, col))
////	{
////		pass_maze(maze, row + 1, col);
////	}
////
////	//向右
////	if (pass_maze(maze, row + 1, col))
////		return true;
////
////	//
////	if (pass_maze(maze, row, col - 1))
////		return true;
////
////
////	//向下
////	if (pass_maze(maze, row + 1, col))
////		return true;
////
////	return false;
////}
//
//Maze::~Maze()
//{
//	if (!m_ptr)
//		return;
//	for (int i = 0; i < m_row; ++i)
//	{
//		delete[] m_ptr[i];
//		m_ptr[i] = nullptr;
//	}
//	delete[] m_ptr;
//	m_ptr = nullptr;
//}
