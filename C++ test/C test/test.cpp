#include <iostream>
using namespace std;

int main()
{
	for (int i = 0; i < 26; ++i)//£¨'a' - 'z'£©-->£¨1 - 26£©
	{
		char ch = 'A' + i;
		cout << (ch ^ 64) << endl;
	}

	for (int i = 0; i < 26; ++i)//£¨'A' - 'Z'£©-->£¨1 - 26£©
	{
		char ch = 'a' + i;
		cout << (ch^96) << endl;
	}

	for (int i = 0; i < 10; ++i)//£¨'0' - '9'£©-->£¨0 - 9£©
	{
		char ch = '0' + i;
		cout << (ch^48) << endl;
	}

	system("pause");
	return 0;
}
