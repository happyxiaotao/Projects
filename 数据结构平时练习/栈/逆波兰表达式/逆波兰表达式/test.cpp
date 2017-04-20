/*

�沨�����ʽ�����Ǻ�׺���ʽ
�����沨�����ʽ��ֵ����Ҫջ����ȡ�����������������
ע��ʹ���ַ������洢�沨�����ʽ���ã�����ʹ���ַ���ָ��
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
			cerr << "��������Ϊ0" << endl;
			assert(0);
		}
		break;
	default:
		break;
	}
}
//�沨�����ʽreverse polish expression
int RPE(char* str)
{
	int str_len = strlen(str);
	stack<char> s;//��������

	for (int i = 0; i < str_len; ++i)
	{
		if (isData(str[i]))//str[i]�����ݣ���ջ
			s.push(str[i]);
		else//str[i]�������ݣ���Ҫ���ж�Ӧ����
			calculate(str[i], s);
	}

	return s.top() - '0';
}

int main()
{	
	//EPR�ǻ���沨�����ʽ�Ľ��
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
