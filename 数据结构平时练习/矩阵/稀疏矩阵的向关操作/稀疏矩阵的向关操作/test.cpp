#include "SparseMatrix.hpp"

const size_t ROW = 6;
const size_t COL = 5;
int Matrix[ROW][COL] = {
	{ 1, 0, 3, 0, 5 },
	{ 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0 },
	{ 1, 0, 3, 0, 5 },
	{ 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0 } };

int main()
{
	SparseMatrix<int> sm((int *)Matrix, 6, 5, 0);
	sm.Acess(3,3);

	system("pasue");
	return 0;
}