
#include <stdio.h>
#include <stdlib.h>
void Print()
{
	printf("��������ѡ��Ĳ�������0-9����\n");
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
			printf("���ǲ���1��ִ�д򿪼��±�����\n");
			system("notepad.exe");
			break;
		case 2:
			p = "del e:\\123.txt";
			printf("���ǲ���2��ִ��ɾ��%s�ļ�����\n","e:\\123.txt");
			system(p);
			break;
		case 3:                    
			p = "shutdown -s -t 60";
			printf("���ǲ���3��ִ��һ���Ӻ�ػ�����\n");
			system(p);
			break;
		case 4:
			p = "shutdown -a";
			printf("���ǲ���4��ִ��ȡ���ػ�����\n");
			system(p);
			break;
		case 5:
			p = "pause";
			printf("���ǲ���5��ִ����ͣ����\n");
			system(p);
			break;
		case 6:
			p = "cls";
			printf("���ǲ���6��ִ����������\n");
			system(p);
			break;
		case 7:
			p = "color 6B";
			printf("���ǲ���7��ִ�иı����̨��ǰ���뱳������\n");
			system(p);
			break;
		case 8:
			p = "regedit";
			printf("���ǲ���8��ִ�д�ע������\n");
			system(p);
			break;
		case 9:
			p = "mode con cols=200 lines=150";
			printf("���ǲ���9��ִ�иı䴰�ڿ�͸߲���\n");
			system(p);
			break;
		default:
			printf("�밴�������룺\n");
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