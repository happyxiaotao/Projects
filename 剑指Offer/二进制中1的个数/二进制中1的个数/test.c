/*输入一个整数，输出该数二进制表示中1的个数。其中负数用补码表示。
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