/*
对称矩阵压缩存储
压缩矩阵：对称矩阵存储时只需要存储上三角或下三角的数据，所以最多存储
n*(n+1)/2个数据。
对称矩阵和对称压缩存储的对应关系：
下三角存储i>=j,SymmetricMatrix[i][j] == Array[i*(i+1)/2+j]
*/
#include <iostream>
using namespace std;

const int MAX_ROW = 5;
const int MAX_COL = MAX_ROW;
int MartixArry[MAX_ROW][MAX_COL] = 
				{{ 0, 1, 2, 3, 4 },
				{ 1, 0, 1, 2, 3 },
				{ 2, 1, 0, 1, 2 },
				{ 3, 2, 1, 0, 1 },
				{ 4, 3, 2, 1, 0 } };

template <class T>
class Martix
{
public :
	Martix(T* p, size_t N)//N为行数
	{
		if (p)
		{
			size_t idx = 0;
			//只需开辟N(N+1)/2个空间即可	
			m_ptr = new T[N*(N + 1) >> 1];
			//向新空间里面放入数据		
			for (size_t i = 0; i < N; ++i)
				for (size_t j = 0; j <= i; ++j)
					m_ptr[idx++] = p[i*N + j];

			m_row = N;
		}
		else
		{
			m_ptr = nullptr;
			m_row = 0;
		}
	}

	T& Access(int i, int j)
	{
		if (i < j)
		{
			::swap(i, j);
		}
		return m_ptr[i*(i + 1) / 2 + j];
	}

	void PrintMartix()
	{
		size_t row = m_row;
		size_t col = m_row;
		for (size_t i = 0; i < row; ++i)
		{
			for (size_t j = 0; j < col; ++j)
				cout << Access(i, j) << " ";
			cout << endl;
		}
	}

	~Martix()
	{
		if (m_ptr)
		{
			delete[] m_ptr;
			m_ptr = nullptr;
			m_row = 0;
		}
	}
private:
	T* m_ptr;
	size_t m_row;
};

int main()
{
	Martix<int> martix((int *)MartixArry, MAX_ROW);

	martix.PrintMartix();

	system("pause");
	return 0;
}