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
//	cout<<(sm1 + sm2);//打印两个稀疏矩阵和的矩阵

	cout << sm1 << endl;
	//cout << sm1.Transport();
	cout<<sm1.FastTransport();//由于内部需要创建数组，所以采取自己给数组大小的方式，所以存在限制（用什么方法解决？）

	system("pause");
	return 0;
}