//һֻ����һ�ο�������1��̨�ף�Ҳ��������2���������������һ��n����̨���ܹ��ж�����������
/*
n = 0  0 f(0)
n = 1, (1) f(1) 
n = 2, (2, 1+1) f(0)+f(1) 
n = 3, (3, 2+1, 1+2) f(0)+f(1)+f(2)
n = 4, (4, 3+1, 2+2, 1+3) f(0)+f(1)+f(2)+f(3)
n = n, (n,n-1+1, n-2+2, ... 1+n-1) f(0)+f(1)+f(2)+...+f(n-1)

f(n) = f(n-1)+f(n-1) = 2*f(n-1)
*/
#include <stdio.h>
int JumpFloor(int number)
{
	int fn = 1;
	if (0 >= number)
		return 0;
	while (--number)
		fn *= 2;
	return fn;

	//���������,����û�������븺�����
//	return  1<<--number;
}
int main()
{
	return 0;
}