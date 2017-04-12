
#include <stdio.h>
#include <stdlib.h>
void Print()
{
	printf("输入你想选择的操作数字0-9均可\n");
}
int Choose()
{
	int choose;
	scanf("%d",&choose);
	return choose;
}
void Operate()
{
	int choose;
	char *p;
	bool flag = true;
	
	do{
		Print();
		choose = Choose();
		switch(choose)
		{
		case 0:
			flag = false;
			break;
		case 1:	
//			p = "notepad.exe";
			printf("这是操作1，执行打开记事本功能\n");
			system("notepad.exe");
			break;
		case 2:
			p = "del e:\\123.txt";
			printf("这是操作2，执行删除%s文件操作\n","e:\\123.txt");
			system(p);
			break;
		case 3:                    
			p = "shutdown -s -t 60";
			printf("这是操作3，执行一分钟后关机操作\n");
			system(p);
			break;
		case 4:
			p = "shutdown -a";
			printf("这是操作4，执行取消关机操作\n");
			system(p);
			break;
		case 5:
			p = "pause";
			printf("这是操作5，执行暂停操作\n");
			system(p);
			break;
		case 6:
			p = "cls";
			printf("这是操作6，执行清屏操作\n");
			system(p);
			break;
		case 7:
			p = "color 6B";
			printf("这是操作7，执行改变控制台的前景与背景操作\n");
			system(p);
			break;
		case 8:
			p = "regedit";
			printf("这是操作8，执行打开注册表操作\n");
			system(p);
			break;
		case 9:
			p = "mode con cols=200 lines=150";
			printf("这是操作9，执行改变窗口宽和高操作\n");
			system(p);
			break;
		default:
			printf("请按规则输入：\n");
			Operate();
		}
	p = NULL;
	}while(flag);	
}
int main()
{
	Operate();
	return 0;
}