/*

逆波兰表达式：就是后缀表达式
计算逆波兰表达式的值：需要栈来获取最近的两个操作数。
注：使用字符串来存储逆波兰表达式不好，尝试使用字符串指针
*/

#include <iostream>
#include <stack>
#include <assert.h>
#include <vector>
using namespace std;
const int maxSize = 20;
const char handle[] = {'+', '-', '*', '/'};

bool isData(char ch)
{
	int len = strlen(handle);
	for (int i = 0; i < len; ++i)
		if (handle[i] == ch)
			return false;
	return true;
}

void calculate(char ch, stack<char>& s)
{
	char right = s.top()-'0';
	s.pop();
	char left = s.top()-'0';
	s.pop();

	switch (ch)
	{
	case '+':
		s.push(left + right + '0');
		break;
	case '-':
		s.push(left - right + '0');
		break;
	case '*':
		s.push(left * right + '0');
		break;
	case '/':
		if (0 != right)
			s.push(left / right + '0');
		else
		{	
			cerr << "除数不能为0" << endl;
			assert(0);
		}
		break;
	default:
		break;
	}
}
//逆波兰表达式reverse polish expression
int RPE(char* str)
{
	int str_len = strlen(str);
	stack<char> s;//保存数据

	for (int i = 0; i < str_len; ++i)
	{
		if (isData(str[i]))//str[i]是数据，入栈
			s.push(str[i]);
		else//str[i]不是数据，需要进行对应操作
			calculate(str[i], s);
	}

	return s.top() - '0';
}

int main()
{	
	//EPR是获得逆波兰表达式的结果
	char str[maxSize];

	while (1)
	{
		cin >> str;

		int result = RPE(str);
		cout << "result = " << result << endl;
	}
	system("pause");
	return 0;
}
