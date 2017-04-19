/*
括号匹配问题：
1，首先在栈顶放一个‘#’表示空栈。
2，获取字符串中的下一个表示括号的字符。
3，判断栈顶元素是否与该括号是否兼容
（	‘#’后面可以放：任意左括号（兼容）；
	左大括号后可以放:右大括号（匹配）、左大括号、左中括号、左小括号（兼容）；
	左中括号可以放：右中括号（匹配）、左中括号、左小括号（兼容）；
	左小括号只后可以放：右小括号（匹配）、左小括号（兼容）
）不兼容也不匹配返回0，兼容返回1,匹配返回2.
4，若只是兼容，就入栈；若匹配，就将栈顶元素出栈；如果不兼容，就退出，并表示字符串括号不匹配。
5，持续2,3,4步，直到遍历完字符串。
*/


/*
拓展：利用智能指针来管理资源
*/
#include <iostream>
#include <stack>
using namespace std;
const int maxSize = 20;


//获取输入的字符串
inline char* InitStr(char* str)
{
	cin >> str;
	return str;
}
//打印字符串
inline void display(char* str)
{
	cout << str << endl;
}

//字符是否是括号
inline bool isBracket(char ch)
{
	if (('{' == ch || '}' == ch)
		|| ('[' == ch || ']' == ch)
		|| ('(' == ch || ')' == ch))
		return true;
	return false;
}

//括号是否兼容或匹配。不兼容，返回0；只兼容，返回1,；匹配，返回2，
char isMatch(char top, char ch)
{
	switch (top)
	{
	case '#'://以'#'表示空栈的好处是，可以统一判断方法
		if (('{' == ch) || ('[' == ch) || ('(' == ch))
			return 1;
		break;
	case '{':
		if ('}' == ch)
			return 2;
		else if (('{' == ch) || ('[' == ch) || ('(' == ch))
			return 1;
		break;
	case '[':
		if (']' == ch)
			return 2;
		else if (('[' == ch) || ('(' == ch))
			return 1;
		break;
	case '(':
		if (')' == ch)
			return 2;
		else if ('(' == ch)
			return 1;
		break;
	default:
		break;
	}
	return 0;
}

//字符串是否括号匹配
bool MatchBrackets(char* str)
{
	stack<char> s;
	s.push('#');//插入一个'#'，表示空栈，统一后面判断括号是否兼容的方法

	int str_len = strlen(str);//获取字符串长度

	for (int i = 0; i < str_len; ++i)
	{
		char ch = str[i];

		if (isBracket(ch))//判断是否是括号，只对括号感兴趣
		{
			char top = s.top();
			char flag = isMatch(top, ch);//注：flag置为char是因为flag有三种状态，bool不够用，而short又太浪费
			if (1 == flag)//只兼容，不匹配，ch入栈
				s.push(ch);
			else if (2 == flag)//括号匹配，栈顶出栈
				s.pop();
			else  //0 == flag
				return false;//括号不兼容，即字符串括号不匹配。
		}
	}
	//如果字符串中的所有字符都兼容的话，返回true
	return true;
}

int main()
{
	char str[maxSize] = {0};

	while (1)
	{
		cout << "输入字符串：";
		InitStr(str);
		cout << "打印字符串：";
		display(str);

		if (MatchBrackets(str))
			cout << "字符串括号匹配" << endl;
		else
			cout << "字符串括号不匹配" << endl;
	}

	system("pause");
	return 0;
}
