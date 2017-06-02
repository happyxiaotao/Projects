//#include "RBTree.hpp"
#include "RBTreeIterator.hpp"

void Test1();//��֤û��iteratorʱ�ĺ����
void Test2();//��֤iteratorΪ��ʱ�����
void Test3();//��֤���iterator�ĺ����

int main()
{
	Test3();
	system("pause");
	return 0;
}

void Test1()
{
	int a[] = { 10,85,15,70,20,60,30,50,65,80,90,40,5,55 };
	//int a[] = { 10, 7, 8, 15, 5, 6, 11, 13, 12 };
	//int a[] = { 1,10,120,3333,51234,123,4123,41,2,3,4,1,23,4,1,23,41,2,34,123,2,3,4,5,6,7,8,9,10 };
	RBTree<int, int> t;
	size_t size = sizeof(a) / sizeof(a[0]);
	for (int i = 0; i < size; ++i)
	{
		if (80 == a[i])//���е�ĳһ�ض����
		{
			cout << "11" << endl;
		}
		t.Insert(a[i], 0);
	}

	t.InOrder();

	if (t.CheckRBTree())
		cout << "������������" << endl;
}

//��֤iteratorΪ��ʱ�����
void Test2()
{	
	//vector<int>::iterator it;
	//cout << *it << endl;
}

void Test3()
{
	int a[] = { 10,85,15,70,20,60,30,50,65,80,90,40,5,55 };//�ȽϺõ����ӣ����ϵ�����
	//int a[] = { 10, 7, 8, 15, 5, 6, 11, 13, 12 };
	//int a[] = { 1,10,120,3333,51234,123,4123,41,2,3,4,1,23,4,1,23,41,2,34,123,2,3,4,5,6,7,8,9,10 };
	RBTree<int, int> t;
	size_t size = sizeof(a) / sizeof(a[0]);
	for (size_t i = 0; i < size; ++i)
	{
		if (80 == a[i])//���е�ĳһ�ض�������������
		{
			cout << endl;
		}
		t.Insert(a[i], 0);
	}

	t.InOrder();
	cout << endl;

	cout << "���õ�������ӡ:" << endl;
	RBTree<int, int>::iterator it;
	it = t.Begin();
	while (it != t.End())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;

	if (t.CheckRBTree())
		cout << "��֤��������������������" << endl;
}