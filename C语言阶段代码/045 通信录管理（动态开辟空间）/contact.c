
#include "contact.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

//初始化Contact
void init_contact(pContact pcon)
{
	assert(pcon);

	memset(pcon, 0, sizeof(Contact));
	
	pcon->_capacity += INIT;

	pcon->_pdata = (pPeoInfo)calloc(pcon->_capacity, sizeof(PeoInfo));
}

//	1，添加联系人信息
void add_contact(pContact pcon)
{
	assert(pcon);

	if (pcon->_sz == MAX)
	{
		printf("联系人个数已达最大值，无法继续添加！\n");
		system("pause");
		return ;
	}
	if (pcon->_sz == pcon->_capacity)
	{
		pcon->_capacity += INIT;
		pcon->_pdata = (pPeoInfo)realloc(pcon->_pdata, sizeof(PeoInfo)*(pcon->_capacity));
	}

	printf("输入该联系人信息：\n");

	printf("姓名：");
	scanf("%s",(pcon->_pdata + pcon->_sz)->_name);

	printf("性别：");
	scanf("%s",(pcon->_pdata + pcon->_sz)->_sex);

	printf("年龄："); 
	scanf("%d",&((pcon->_pdata + pcon->_sz)->_age));

	printf("电话："); 
	scanf("%s",(pcon->_pdata + pcon->_sz)->_tel);

	printf("地址："); 
	scanf("%s",(pcon->_pdata + pcon->_sz)->_addr);

	printf("添加成功！\n");

	++ pcon->_sz;

	system("pause");
}

//	2，删除指定联系人信息
void delete_contact(pContact pcon)
{
	int index = -1;

	assert(pcon);

	if (0 == pcon->_sz)
	{
		printf("通信录为空，无法执行删除操作!\n");

		system("pause");
		return ;
	}

	index = find_name(pcon);

	if (-1 == index)
	{
		printf("未找到该联系人!\n");

		system("pause");
		return ;
	}

	if (pcon->_sz - 1 > index)
	{	
		int i = 0;
		//无需重置最后一个数据内容
		for (i = index; i < pcon->_sz - 1; i++)
		{
			swap_info(pcon->_pdata+i, pcon->_pdata+i+1, sizeof(PeoInfo));
		}

		printf("删除成功！\n");

		system("pause");
	}

	//只需将_sz指向前一位
	-- pcon->_sz;
	
}

//	3，查找联系人信息
void search_contact(pContact pcon)
{
	int index = -1;

	assert(pcon);
	
	index = find_name(pcon);

	if (-1 != index)
	{
		printf("查找成功！\n");

		printf("%10s%10s%10s%10s%10s\n",
			"姓名","性别","年龄","电话","住址");
		showinfo(pcon, index);

		system("pause");

		return ;
	}

	printf("查找失败！\n");

	system("pause");
}

//	4，修改联系人信息
void modify_contact(pContact pcon)
{
	int index = -1;
	
	assert(pcon);
	
	index = find_name(pcon);

	if (-1 == index)
	{
		printf("未找到该联系人！\n");

		system("pause");

		return ;
	}
	else
	{
		printf("输入该联系人信息：\n");

		printf("姓名：");
		scanf("%s", (pcon->_pdata + index)->_name);

		printf("性别："); 
		scanf("%s", (pcon->_pdata + index)->_sex);

		printf("年龄："); 
		scanf("%d", (pcon->_pdata + index)->_age);

		printf("电话：");
		scanf("%s", (pcon->_pdata + index)->_tel);

		printf("地址："); 
		scanf("%s", (pcon->_pdata + index)->_addr);

		printf("修改成功！\n");
	}
}

//	5，显示所有联系人信息
void display_contact(pContact pcon)
{
	int i = 0;
		
	assert(pcon);

	if (0 == pcon->_sz)
	{
		printf("通信录信息为空！\n");

		system("pause");

		return ;
	}

	//显示所有联系人信息
	printf("%10s%10s%10s%10s%10s\n",
		"姓名","性别","年龄","电话","住址");
	for (i = 0; i < pcon->_sz; i++)
	{
		showinfo(pcon, i);
	}

	system("pause");
}

//	6，清空所有联系人信息
void empty_contact(pContact pcon)
{
	int i = 0;

	assert(pcon);

	memset(pcon, 0, sizeof(Contact));

	pcon->_sz = 0;
	free(pcon->_pdata);
	pcon->_pdata = NULL;

	printf("清空成功！\n");

	system("pause");
}

//	7，以名字排序所有联系人
void sort_contact(pContact pcon)
{
	int i = 0;
	assert(pcon);

	for (i = 0; i < pcon->_sz - 1; i++)
	{
		int j = 0;

		for (j = 0; j < pcon->_sz - 1 - i; j++)
		{
			if (strcmp((pcon->_pdata + i)->_name, (pcon->_pdata + i+1)->_name) > 0)
			{
				swap_info(pcon->_pdata + i, pcon->_pdata + i+1, sizeof(PeoInfo));
			}
		}
	}

	printf("排序成功！\n");

	display_contact(pcon);
}

//查找名字为name的人
int find_name(pContact pcon)
{
	char name[MAX_NAME] = {0};
	int i = 0;

	printf("输入该联系人名字 > ");
	scanf("%s", name);
	
	for (i = 0; i < pcon->_sz; i++)
	{
		if (0 == strcmp(name, (pcon->_pdata + i)->_name))
		{
			return i;
		}
	}

	return -1;
}

//显示第i个联系人信息
void showinfo(pContact pcon, int i)
{
	printf("%10s", (pcon->_pdata + i)->_name);
	printf("%10s", (pcon->_pdata + i)->_sex);
	printf("%10d", (pcon->_pdata + i)->_age);
	printf("%10s", (pcon->_pdata + i)->_tel);
	printf("%10s\n", (pcon->_pdata + i)->_addr);
}

//交换空间内容
void swap_info(void *dest, void *src, int n)
{
	int i = 0;

	for (i = 0; i < n; i++)
	{
		char tmp = *((char *)dest + i);
		*((char *)dest + i) = *((char *)src + i);
		*((char *)src + i) = tmp;
	}
}