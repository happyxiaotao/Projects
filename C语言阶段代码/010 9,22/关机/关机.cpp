#include <stdlib.h>
#include <stdio.h>
#include <string.h>
int main()
{

	char choose[20];
	int flag = 1;
	system("shutdown -s -t 60");

	while(flag)
	{	
		printf("输入“我是猪”：不然的话一分钟后电脑会自动关机哦\n输入>");
		scanf("%s",&choose);
		if(strcmp(choose,"我是猪") == 0)
			flag = 0;
		else
			system("shutdown -a");
	}
	printf("已取消关机！\n");
	printf("哼哼，算你识相！\n");

	system("pause");
	return 0;
}