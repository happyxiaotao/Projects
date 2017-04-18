/*
�Գƾ���ѹ���洢
ѹ�����󣺶Գƾ���洢ʱֻ��Ҫ�洢�����ǻ������ǵ����ݣ��������洢
n*(n+1)/2�����ݡ�
�Գƾ���ͶԳ�ѹ���洢�Ķ�Ӧ��ϵ��
�����Ǵ洢i>=j,SymmetricMatrix[i][j] == Array[i*(i+1)/2+j]
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
	Martix(T* p, size_t N)//NΪ����
	{
		if (p)
		{
			size_t idx = 0;
			//ֻ�迪��N(N+1)/2���ռ伴��	
			m_ptr = new T[N*(N + 1) >> 1];
			//���¿ռ������������		
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