#include <iostream>

using namespace std;

class A
{
public :
	A(int a, int b, int c) :_a(a), _c(b), _b(c)
	{}
	void Print()
	{
		cout << _a << endl;
		cout << _b << endl;
		cout << _c << endl;
	}
private:
	int _a;
	int _b;
	int _c;
};
int main()
{
	A a(1,2,3);
	a.Print();

	system("pause");
	return 0;
}