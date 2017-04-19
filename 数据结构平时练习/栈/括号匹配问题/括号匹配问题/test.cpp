/*
����ƥ�����⣺
1��������ջ����һ����#����ʾ��ջ��
2����ȡ�ַ����е���һ����ʾ���ŵ��ַ���
3���ж�ջ��Ԫ���Ƿ���������Ƿ����
��	��#��������Էţ����������ţ����ݣ���
	������ź���Է�:�Ҵ����ţ�ƥ�䣩��������š��������š���С���ţ����ݣ���
	�������ſ��Էţ��������ţ�ƥ�䣩���������š���С���ţ����ݣ���
	��С����ֻ����Էţ���С���ţ�ƥ�䣩����С���ţ����ݣ�
��������Ҳ��ƥ�䷵��0�����ݷ���1,ƥ�䷵��2.
4����ֻ�Ǽ��ݣ�����ջ����ƥ�䣬�ͽ�ջ��Ԫ�س�ջ����������ݣ����˳�������ʾ�ַ������Ų�ƥ�䡣
5������2,3,4����ֱ���������ַ�����
*/


/*
��չ����������ָ����������Դ
*/
#include <iostream>
#include <stack>
using namespace std;
const int maxSize = 20;


//��ȡ������ַ���
inline char* InitStr(char* str)
{
	cin >> str;
	return str;
}
//��ӡ�ַ���
inline void display(char* str)
{
	cout << str << endl;
}

//�ַ��Ƿ�������
inline bool isBracket(char ch)
{
	if (('{' == ch || '}' == ch)
		|| ('[' == ch || ']' == ch)
		|| ('(' == ch || ')' == ch))
		return true;
	return false;
}

//�����Ƿ���ݻ�ƥ�䡣�����ݣ�����0��ֻ���ݣ�����1,��ƥ�䣬����2��
char isMatch(char top, char ch)
{
	switch (top)
	{
	case '#'://��'#'��ʾ��ջ�ĺô��ǣ�����ͳһ�жϷ���
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

//�ַ����Ƿ�����ƥ��
bool MatchBrackets(char* str)
{
	stack<char> s;
	s.push('#');//����һ��'#'����ʾ��ջ��ͳһ�����ж������Ƿ���ݵķ���

	int str_len = strlen(str);//��ȡ�ַ�������

	for (int i = 0; i < str_len; ++i)
	{
		char ch = str[i];

		if (isBracket(ch))//�ж��Ƿ������ţ�ֻ�����Ÿ���Ȥ
		{
			char top = s.top();
			char flag = isMatch(top, ch);//ע��flag��Ϊchar����Ϊflag������״̬��bool�����ã���short��̫�˷�
			if (1 == flag)//ֻ���ݣ���ƥ�䣬ch��ջ
				s.push(ch);
			else if (2 == flag)//����ƥ�䣬ջ����ջ
				s.pop();
			else  //0 == flag
				return false;//���Ų����ݣ����ַ������Ų�ƥ�䡣
		}
	}
	//����ַ����е������ַ������ݵĻ�������true
	return true;
}

int main()
{
	char str[maxSize] = {0};

	while (1)
	{
		cout << "�����ַ�����";
		InitStr(str);
		cout << "��ӡ�ַ�����";
		display(str);

		if (MatchBrackets(str))
			cout << "�ַ�������ƥ��" << endl;
		else
			cout << "�ַ������Ų�ƥ��" << endl;
	}

	system("pause");
	return 0;
}
