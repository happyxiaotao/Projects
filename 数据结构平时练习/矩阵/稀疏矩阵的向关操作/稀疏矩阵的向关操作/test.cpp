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
	//const SparseMatrix<int> sm((int *)Matrix, 6, 5, 0);
	//cout<<sm.Access(0,0);
	//cout << "´òÓ¡Ï¡Êè¾ØÕó£º" << endl << sm << endl;

	SparseMatrix<int> sm1((int *)Matrix, 6, 5, 0);
	const SparseMatrix<int> sm2((int *)Matrix, 6, 5, 0);
	cout<<(sm1 + sm2);

	system("pause");
	return 0;
}