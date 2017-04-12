#include <stdio.h>
#include <stdlib.h>
int main()
{
	int rows = 15;
	int i = 0, j = 0;
	int count = 0;
	//设置数组大小为rows*（rows）/ 2 = 120
	int Yanghui[120] = {0};

	system("mode con cols=150 lines=100");

	printf("%d行杨辉三角如下所示：\n",rows);

	for(i = 0; i < rows; i++)
	{
		for(j = 0; j < rows -1 - i; j++)
		{
			printf("    ");
		}

		for(j = 0; j <= i; j++)
		{
			int left = i*(i+1)/2;//该行最左边数组下标
			int right = (i+1)*(i+2)/2-1;//该行最右边数组下标
			int last_low = count-i-1;//上一行所需两数中小的数
			int last_high = count-i;//上一行所需两数中大的数
			Yanghui[count] = Yanghui[last_low] + Yanghui[last_high];
			Yanghui[left] = Yanghui[right] = 1;//重新赋值，避免值不为1
			printf("%4d",Yanghui[count++]);
			printf("    ");
		}
		printf("\n");
	}

	printf("\n一共有%d个数\n",count);

	return 0;
}