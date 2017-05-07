#include "BinaryTreeTh.hpp"

void FunTest1();

int main()
{
	FunTest1();

	system("pause");
	return 0;
}

void FunTest1()
{
	char* str = "124###35##6";

	BinaryTreeTh<char> t = BinaryTreeTh<char>(str, strlen(str), '#');

	t.PreThreading();


}