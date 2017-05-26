#include <iostream>
#include "new_delete.h"

/*
对于new 与delete 《more effective C++》有详细的叙述
*/

using namespace std;

class Array
{
public :
	Array();
	const int & operator[](int idex) const;
	int& operator[] (int idex);
private :
	int* array;
};

Array::Array():array(new int[10])
{
	for (int idex = 0; idex < 10; ++idex)
		array[idex] = idex;
}
const int& Array::operator[] (int idex)const
{
	return array[idex];
}
int& Array::operator[] (int idex)
{
	return array[idex];
}

int main()
{
	const Array a1;

	cout << a1[2] << endl;
	system("pause");
	return 0;
}