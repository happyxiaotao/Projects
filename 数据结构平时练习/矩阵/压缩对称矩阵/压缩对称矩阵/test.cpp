/*
�Գƾ���ѹ���洢
ѹ�����󣺶Գƾ���洢ʱֻ��Ҫ�洢�����ǻ������ǵ����ݣ��������洢
n*(n+1)/2�����ݡ�
�Գƾ���ͶԳ�ѹ���洢�Ķ�Ӧ��ϵ��
�����Ǵ洢i>=j,SymmetricMatrix[i][j] == Array[i*(i+1)/2+j]
i*(i+1)/2�ǵ���������͹�ʽ����ʾǰi�и�������������0��ʼ�ģ�
i*(i+1)/2+j��ʾѹ����i��j�ж�Ӧ�ĵ��λ�á���������0��ʼ�ģ�
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
	Martix(T* p, size_t N)//NΪ����
	{
		if (p)
		{
			size_t idx = 0;
			//ֻ�迪��N(N+1)/2���ռ伴��	
			m_pData = new T[N*(N + 1) >> 1];
			//���¿ռ������������		
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
		//static_cast:��Martix<T>* const this���ϳ��ԣ���Ϊconst Martix<T>* const this
		//const_cast:�����ص�const T&ȥ���ԣ���ΪT&����
	}

	const T& Access(int i, int j)const
	{
		if (i < j)//���ڴ洢����������Ԫ��
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

	cout << martix << endl;//��ӡ�Գƾ���

	martix.Access(3, 3) = 10;//�Ծ�������޸�

	cout << martix << endl;//��ӡ�Գƾ���

	system("pause");
	return 0;
}