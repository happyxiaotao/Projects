#include "SparseMatrix.hpp"

const size_t ROW = 6;
const size_t COL = 5;
int Matrix1[ROW][COL] = {
	{ 1, 0, 3, 0, 5 },
	{ 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0 },
	{ 1, 0, 3, 0, 5 },
	{ 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0 } };
int Matrix2[ROW][COL] = {
	{ 0, 0, -3, 0, 5 },
	{ 3, 0, 0, 0, 0 },
	{ 0, 4, 0, 0, 9 },
	{ -1, 0, 4, 0, 5 },
	{ 0, 0, 0, 4, 0 },
	{ 0, 0, 0, 0, 4 } };

int main()
{
	SparseMatrix<int> sm1((int *)Matrix1, 6, 5, 0);
	const SparseMatrix<int> sm2((int *)Matrix2, 6, 5, 0);
//	cout<<(sm1 + sm2);//��ӡ����ϡ�����͵ľ���

	cout << sm1 << endl;
	//cout << sm1.Transport();
	cout<<sm1.FastTransport();//�����ڲ���Ҫ�������飬���Բ�ȡ�Լ��������С�ķ�ʽ�����Դ������ƣ���ʲô�����������

	system("pause");
	return 0;
}