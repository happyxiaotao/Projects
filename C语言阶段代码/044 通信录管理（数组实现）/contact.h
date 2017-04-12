#ifndef __CONTACT__H__
#define __CONTACT__H__

#define MAX 1000 //人数最大容量
#define MAX_NAME 15
#define MAX_SEX 5
#define MAX_TEL 12
#define MAX_ADDR 32

typedef struct PeoInfo
{
	char _name[MAX_NAME];
	char _sex[MAX_SEX];
	int _age;
	char _tel[MAX_TEL];
	char _addr[MAX_ADDR];
}PeoInfo, *pPeoInfo;

typedef struct Contact
{
	PeoInfo  _data[MAX];
	int _sz;
}Contact, *pContact;

enum Un
{
	EXIT,
	ADD,
	DELETE,
	SEARCH,
	MODIFY,
	DISPLAY,
	EMPTY,
	SORT,
};

//初始化Contact
void init_contact(pContact pcon);

//	1，添加联系人信息
void add_contact(pContact pcon);

//	2，删除指定联系人信息
void delete_contact(pContact pcon);

//	3，查找联系人信息
void search_contact(pContact pcon);

//	4，修改联系人信息
void modify_contact(pContact pcon);

//	5，显示所有联系人信息
void display_contact(pContact pcon);

//	6，清空所有联系人信息
void empty_contact(pContact pcon);

//	7，以名字排序所有联系人
void sort_contact(pContact pcon);


//查找名字为name的人
int find_name(pContact pcon);

//显示第i个联系人信息
void showinfo(pContact pcon, int i);

//交换空间内容
void swap_info(char *dest, char *src, int n);

#endif //__CONTACT__H__