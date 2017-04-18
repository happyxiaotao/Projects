#include "Stack.hpp"
#include <vector>
#include <stack>

int main()
{
	//test1
	//Stack<int> s1;
	////s1.Push(1);
	////s1.Push(2);
	////s1.Push(3);
	////s1.Push(4);
	////s1.Push(5);
	//s1.Push(6);
	//
	//Stack<int> s2(s1);
	//Stack<int> s3;
	//s3 = s2;

	//s3.Top();

	//test2
	//Stack<char*> s1;
	//s1.Push("abcd1");
	//s1.Push("abcd2");
	//s1.Push("abcd3");
	//s1.Push("abcd4");
	//cout<<s1.Top()<<endl;

	//Stack<char*> s2(s1);
	//Stack<char*> s3;
	//s3 = s2;

	//test3
	Stack<vector<int>> s1;
	vector<int> v1(2, 5);
	vector<int> v2(2, 6);
	vector<int> v3(2, 7);
	vector<int> v4(2, 8);
	vector<int> v5(2, 9);
	s1.Push(v1);
	s1.Push(v2);
	s1.Push(v3);
	s1.Push(v4);
	s1.Push(v5);

	Stack<vector<int>> s2(s1);
	Stack<vector<int>> s3;
	s3 = s2;

	//test4
	//stack<int> s1;
	//s1.push(1);
	//s1.push(2);
	//s1.push(3);
	//s1.push(4);
	//s1.push(5);
	//stack<int> s2(s1);
	//stack<int> s3;
	//s3 = s2;

	system("pause");
	return 0;
}