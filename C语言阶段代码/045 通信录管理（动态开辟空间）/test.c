/*
Copyrights (c) 2016, 西科大8555室石俊涛
All rights resverse

文件名称：
文件标识：
摘    要：

当前版本：
作    者：石俊涛
完成日期：2016/11/24
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

void menu_main() //主菜单
{
	printf("************     进入主菜单    **********\n");
	printf("*****************************************\n");
	printf("*******         主菜单            *******\n");
	printf("*******     1，管理通讯录         *******\n");
	printf("*******     0，退出通讯录         *******\n");
	printf("*****************************************\n");
}
void menu_sub() //管理界面
{
	printf("************    进入管理界面   **********\n");
	printf("*****************************************\n");
	printf("*******         管理菜单          *******\n");
	printf("*******  1，添加联系人信息        *******\n");
	printf("*******  2，删除指定联系人信息    *******\n");
	printf("*******  3，查找联系人信息        *******\n");
	printf("*******  4，修改联系人信息        *******\n");
	printf("*******  5，显示所有联系人信息    *******\n");
	printf("*******  6，清空所有联系人信息    *******\n");
	printf("*******  7，以名字排序所有联系人  *******\n");
	printf("*******  0，退出子菜单            *******\n");
	printf("*****************************************\n");
}

void manage() //管理菜单
{
	Contact my_con;

	int input = 0;

	//初始化my_con
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
			//	1，添加联系人信息
			add_contact(&my_con);
			break;
		case DELETE:
			//	2，删除指定联系人信息
			delete_contact(&my_con);
			break;
		case SEARCH:
			//	3，查找联系人信息
			search_contact(&my_con);
			break;
		case MODIFY:
			//	4，修改联系人信息
			modify_contact(&my_con);
			break;
		case DISPLAY:
			//	5，显示所有联系人信息
			display_contact(&my_con);
			break;
		case EMPTY:
			//	6，清空所有联系人信息
			empty_contact(&my_con);
			break;
		case SORT:
			//	7，以名字排序所有联系人
			sort_contact(&my_con);
			break;
		case EXIT:
			//  0，退出管理界面
			system("cls");
			break;
		default :
			printf("请按要求输入\n");
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
			printf("退出成功！\n");
			break;
		default :
			printf("请按要求输入\n");
			break;
		}

	} while (input);

	system("pause");
	return 0;
}
