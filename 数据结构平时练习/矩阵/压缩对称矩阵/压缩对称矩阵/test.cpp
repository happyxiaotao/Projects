/*
对称矩阵压缩存储
压缩矩阵：对称矩阵存储时只需要存储上三角或下三角的数据，所以最多存储
n*(n+1)/2个数据。
对称矩阵和对称压缩存储的对应关系：
下三角存储i>=j,SymmetricMatrix[i][j] == Array[i*(i+1)/2+j]
i*(i+1)/2是递增数列求和公式（表示前i行个数）（行数从0开始的）
i*(i+1)/2+j表示压缩后，i行j列对应的点的位置。（列数从0开始的）
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
public:
	Martix(T* p, size_t N)//N为行数
	{
		if (p)
		{
			size_t idx = 0;
			//只需开辟N(N+1)/2个空间即可	
			m_pData = new T[N*(N + 1) >> 1];
			//向新空间里面放入数据		
			for (size_t i = 0; i < N; ++i)
				for (size_t j = 0; j <= i; ++j)
					m_pData[idx++] = p[i*N + j];

			m_row = N;
			m_col = N;
		}
		else
		{
			m_pData = nullptr;
			m_row = 0;
			m_col = 0;
		}
	}

	~Martix()
	{
		if (m_pData)
		{
			delete[] m_pData;
			m_pData = nullptr;
			m_row = 0;
			m_col = 0;
		}
	}

	T& Access(int i, int j)
	{
		return const_cast<T&>(static_cast<const Martix<T>*>(this)->Access(i, j));	
		//static_cast:给Martix<T>* const this加上常性，变为const Martix<T>* const this
		//const_cast:给返回的const T&去常性，变为T&类型
	}

	const T& Access(int i, int j)const
	{
		if (i < j)//由于存储的是下三角元素
		{
			::swap(i, j);
		}
		return m_pData[i*(i + 1) / 2 + j];
	}

public:
	friend ostream& operator << (ostream& out, const Martix<T>& martix)
	{
		for (size_t i = 0; i < martix.m_row; ++i)
		{
			for (size_t j = 0; j < martix.m_col; ++j)
				cout << martix.Access(i, j) << " ";
			cout << endl;
		}
		return out;
	}
private:
	T* m_pData;
	size_t m_row;
	size_t m_col;
};

int main()
{
	Martix<int> martix((int *)MartixArry, MAX_ROW);

	cout << martix << endl;//打印对称矩阵

	martix.Access(3, 3) = 10;//对矩阵进行修改

	cout << martix << endl;//打印对称矩阵

	system("pause");
	return 0;
}