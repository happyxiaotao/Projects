/*
Copyrights (c) 2016, ���ƴ�8555��ʯ����
All rights resverse

�ļ����ƣ�
�ļ���ʶ��
ժ    Ҫ��

��ǰ�汾��
��    �ߣ�ʯ����
������ڣ�2016/11/24
*/

#include "contact.h"
/* Define NULL pointer value */
#ifndef NULL
#ifdef __cplusplus
#define NULL    0
#else  /* __cplusplus */
#define NULL    ((void *)0)
#endif  /* __cplusplus */
#endif  /* NULL */

void menu_main() //���˵�
{
	printf("************     �������˵�    **********\n");
	printf("*****************************************\n");
	printf("*******         ���˵�            *******\n");
	printf("*******     1������ͨѶ¼         *******\n");
	printf("*******     0���˳�ͨѶ¼         *******\n");
	printf("*****************************************\n");
}
void menu_sub() //�������
{
	printf("************    ����������   **********\n");
	printf("*****************************************\n");
	printf("*******         ����˵�          *******\n");
	printf("*******  1�������ϵ����Ϣ        *******\n");
	printf("*******  2��ɾ��ָ����ϵ����Ϣ    *******\n");
	printf("*******  3��������ϵ����Ϣ        *******\n");
	printf("*******  4���޸���ϵ����Ϣ        *******\n");
	printf("*******  5����ʾ������ϵ����Ϣ    *******\n");
	printf("*******  6�����������ϵ����Ϣ    *******\n");
	printf("*******  7������������������ϵ��  *******\n");
	printf("*******  0���˳��Ӳ˵�            *******\n");
	printf("*****************************************\n");
}

void manage() //����˵�
{
	Contact my_con;

	int input = 0;

	//��ʼ��my_con
	init_contact(&my_con);

	do
	{	
		system("cls");

		menu_sub();

		printf("input > ");
		scanf("%d", &input);

		switch (input)
		{
		case ADD:
			//	1�������ϵ����Ϣ
			add_contact(&my_con);
			break;
		case DELETE:
			//	2��ɾ��ָ����ϵ����Ϣ
			delete_contact(&my_con);
			break;
		case SEARCH:
			//	3��������ϵ����Ϣ
			search_contact(&my_con);
			break;
		case MODIFY:
			//	4���޸���ϵ����Ϣ
			modify_contact(&my_con);
			break;
		case DISPLAY:
			//	5����ʾ������ϵ����Ϣ
			display_contact(&my_con);
			break;
		case EMPTY:
			//	6�����������ϵ����Ϣ
			empty_contact(&my_con);
			break;
		case SORT:
			//	7������������������ϵ��
			sort_contact(&my_con);
			break;
		case EXIT:
			//  0���˳��������
			system("cls");
			break;
		default :
			printf("�밴Ҫ������\n");
			break;
		}
	} while (input);

	free(my_con._pdata);
	my_con._pdata = ((void *)0);
}

int main()
{
	int input = 0;

	do 
	{		
		menu_main();

		printf("input > ");
		scanf("%d", &input);

		switch (input)
		{
		case 1:
			manage();
			break;
		case 0:
			system("cls");
			printf("�˳��ɹ���\n");
			break;
		default :
			printf("�밴Ҫ������\n");
			break;
		}

	} while (input);

	system("pause");
	return 0;
}
