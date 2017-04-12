/*
���ܣ�һֻ����һ�ο�������1��̨�ף�Ҳ��������2���������������һ��n����̨���ܹ��ж�����������
������
n = 1, (1)
n = 2, (2,1+1)
n = 3, (2+1,1+2) f(3)=f(1)+f(2)
n = 4, (2+2,1+3) f(4)=f(2)+f(3)
n = n, (2+n-2,1+n-1) f(n)=f(n-2)+f(n-1)
*/

//��һ��
//int jumpFloor(int number) 
//{
//	if (0 >= number)
//		return 0;
//	if ((1 == number) || (2 == number))
//		return number;
//	return (jumpFloor(number-1) + jumpFloor(number-2));
//}
//�ڶ���
//int jumpFloor(int number)
//{
//	int j1 = 1;
//	int j2 = 2;
//	int sum = 0;
//
//	if (number <= 0)
//		return 0;
//	if ((1 == number) || (2 == number))
//		return number;
//	while (3 <= number)
//	{
//		sum = j1 + j2;
//		j1 = j2;
//		j2 = sum;
//		number--;
//	}
//	return sum;
//}
//������
#include <stdio.h>
int jumpFloor(int number)
{
	if (0 >= number)
		return 0;
	int a = 1;
	int b = 2;
	int c = 0;
	while (number-- > 0)
	{
		c = a+b;
		a = b;
		b = c;
	}
	return a;
}

int main()
{
	int ret = jumpFloor(-1);
	ret = jumpFloor(0);
	ret = jumpFloor(1);
	ret = jumpFloor(2);
	ret = jumpFloor(3);
	ret = jumpFloor(4);
	return 0;
}