#ifndef __CONTACT__H__
#define __CONTACT__H__

#define MAX 1000 //�����������
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

//��ʼ��Contact
void init_contact(pContact pcon);

//	1�������ϵ����Ϣ
void add_contact(pContact pcon);

//	2��ɾ��ָ����ϵ����Ϣ
void delete_contact(pContact pcon);

//	3��������ϵ����Ϣ
void search_contact(pContact pcon);

//	4���޸���ϵ����Ϣ
void modify_contact(pContact pcon);

//	5����ʾ������ϵ����Ϣ
void display_contact(pContact pcon);

//	6�����������ϵ����Ϣ
void empty_contact(pContact pcon);

//	7������������������ϵ��
void sort_contact(pContact pcon);


//��������Ϊname����
int find_name(pContact pcon);

//��ʾ��i����ϵ����Ϣ
void showinfo(pContact pcon, int i);

//�����ռ�����
void swap_info(char *dest, char *src, int n);

#endif //__CONTACT__H__