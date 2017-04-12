/*#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
int main()
{
	int i = 0, num = 0;
	char arr[] = "";
	
	num = strlen(arr);

	printf("最终彩票是：\n");
	while(i <= (num+1)/2)
	{
//		Sleep(1000);
//		printf("\a"); 
		puts(arr);
		arr[i] = arr[num-1-i] = '#';
		i++;
	}

	system("pause");

	return 0;
}*/

/*求二进制*/
int GetBinary(int value, int arr[])
{
	int remainder = 0;
	int count = 0;
	int i = 0;

	while(value)
	{
		remainder = value % 2;
		value = value / 2;
		arr[i++] = remainder;
		count++;                                                                        
	};

	return count; 
}

#include <stdio.h>
int main()
{ 
//	int a=0,b=0,m=0,e=0;
	int a=1,b=12996,m=37909,e=227;
	int arr[32] = {0};
	int len = 0;
	int i = 0;
	int temp_b = 0,temp_a = 0;
	
//	printf("输入a,b,m,esp的值：");

//	scanf("%d %d %d",&b,&m,&e);

	len = GetBinary(e, arr);

	for(i = 0; i < len-1; i++)//arr[len-i-1]
	{
		int bin = arr[len-i-1];
	
		if(bin == 1)
		{
			if(i == 0)
			{
				temp_a = b;
				temp_b = temp_a*temp_a % m;
				continue;
			}
			a = b*temp_b;
		}
		else
		{
			if(i == 0)
			{
				temp_a = 1;
				temp_b = temp_a*temp_a % m;
				continue;
			}
			a = temp_b;
		}

		temp_b = temp_a*temp_a % m;
	}

	temp_a = b*temp_b % m;

	printf("模重复平方计算法解得：%d\n",temp_a);

	return 0;
}