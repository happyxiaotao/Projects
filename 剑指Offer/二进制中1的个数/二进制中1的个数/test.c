/*����һ��������������������Ʊ�ʾ��1�ĸ��������и����ò����ʾ��
*/

int numberOf1(int n)
{
	int number = 0;
	while (n)
	{
		n &= n-1;
		number++;
	}	
	return number;
}
int main()
{
	int i = -2;
	while (i < 3)
	{
		printf("i = %d, numberOf1 = %d\n", i, numberOf1(i));
		i++;
	}
	return 0;
}