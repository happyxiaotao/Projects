#include "CirularQueue.hpp"

void test1()
{
	CirQueue<int> cq;

	//��һ������
	cq.Push(10);
	cq.Push(11);
	cq.Push(12);
	cq.Push(13);
	cq.Push(14);
	cq.Push(15);
	cq.Push(16);

	cq.Pop();
	cq.Pop();
	cq.Pop();
	cq.Push(11);
	cq.Push(12);
	cq.Push(13);
	cq.Push(14);
	cq.Push(15);
	cq.Push(16);

	cout << cq.Front() << endl;
	cout << cq.Back() << endl;
	cout << cq.Empty() << endl;
	cout << cq.Size() << endl;

	//�ڶ�������
	cout << endl;
	cq.Pop();
	cq.Pop();

	cout << cq.Front() << endl;
	cout << cq.Back() << endl;
	cout << cq.Empty() << endl;
	cout << cq.Size() << endl;

	//����������
	cout << endl;
	cq.Pop();
	cq.Pop();
	cq.Pop();
	cq.Pop();

	cout << cq.Front() << endl;
	cout << cq.Back() << endl;
	cout << cq.Empty() << endl;
	cout << cq.Size() << endl;

}

int main()
{
	test1();

	system("pause");
	return 0;
}