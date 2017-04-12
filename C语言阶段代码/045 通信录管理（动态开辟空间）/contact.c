
#include "contact.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

//��ʼ��Contact
void init_contact(pContact pcon)
{
	assert(pcon);

	memset(pcon, 0, sizeof(Contact));
	
	pcon->_capacity += INIT;

	pcon->_pdata = (pPeoInfo)calloc(pcon->_capacity, sizeof(PeoInfo));
}

//	1�������ϵ����Ϣ
void add_contact(pContact pcon)
{
	assert(pcon);

	if (pcon->_sz == MAX)
	{
		printf("��ϵ�˸����Ѵ����ֵ���޷�������ӣ�\n");
		system("pause");
		return ;
	}
	if (pcon->_sz == pcon->_capacity)
	{
		pcon->_capacity += INIT;
		pcon->_pdata = (pPeoInfo)realloc(pcon->_pdata, sizeof(PeoInfo)*(pcon->_capacity));
	}

	printf("�������ϵ����Ϣ��\n");

	printf("������");
	scanf("%s",(pcon->_pdata + pcon->_sz)->_name);

	printf("�Ա�");
	scanf("%s",(pcon->_pdata + pcon->_sz)->_sex);

	printf("���䣺"); 
	scanf("%d",&((pcon->_pdata + pcon->_sz)->_age));

	printf("�绰��"); 
	scanf("%s",(pcon->_pdata + pcon->_sz)->_tel);

	printf("��ַ��"); 
	scanf("%s",(pcon->_pdata + pcon->_sz)->_addr);

	printf("��ӳɹ���\n");

	++ pcon->_sz;

	system("pause");
}

//	2��ɾ��ָ����ϵ����Ϣ
void delete_contact(pContact pcon)
{
	int index = -1;

	assert(pcon);

	if (0 == pcon->_sz)
	{
		printf("ͨ��¼Ϊ�գ��޷�ִ��ɾ������!\n");

		system("pause");
		return ;
	}

	index = find_name(pcon);

	if (-1 == index)
	{
		printf("δ�ҵ�����ϵ��!\n");

		system("pause");
		return ;
	}

	if (pcon->_sz - 1 > index)
	{	
		int i = 0;
		//�����������һ����������
		for (i = index; i < pcon->_sz - 1; i++)
		{
			swap_info(pcon->_pdata+i, pcon->_pdata+i+1, sizeof(PeoInfo));
		}

		printf("ɾ���ɹ���\n");

		system("pause");
	}

	//ֻ�轫_szָ��ǰһλ
	-- pcon->_sz;
	
}

//	3��������ϵ����Ϣ
void search_contact(pContact pcon)
{
	int index = -1;

	assert(pcon);
	
	index = find_name(pcon);

	if (-1 != index)
	{
		printf("���ҳɹ���\n");

		printf("%10s%10s%10s%10s%10s\n",
			"����","�Ա�","����","�绰","סַ");
		showinfo(pcon, index);

		system("pause");

		return ;
	}

	printf("����ʧ�ܣ�\n");

	system("pause");
}

//	4���޸���ϵ����Ϣ
void modify_contact(pContact pcon)
{
	int index = -1;
	
	assert(pcon);
	
	index = find_name(pcon);

	if (-1 == index)
	{
		printf("δ�ҵ�����ϵ�ˣ�\n");

		system("pause");

		return ;
	}
	else
	{
		printf("�������ϵ����Ϣ��\n");

		printf("������");
		scanf("%s", (pcon->_pdata + index)->_name);

		printf("�Ա�"); 
		scanf("%s", (pcon->_pdata + index)->_sex);

		printf("���䣺"); 
		scanf("%d", (pcon->_pdata + index)->_age);

		printf("�绰��");
		scanf("%s", (pcon->_pdata + index)->_tel);

		printf("��ַ��"); 
		scanf("%s", (pcon->_pdata + index)->_addr);

		printf("�޸ĳɹ���\n");
	}
}

//	5����ʾ������ϵ����Ϣ
void display_contact(pContact pcon)
{
	int i = 0;
		
	assert(pcon);

	if (0 == pcon->_sz)
	{
		printf("ͨ��¼��ϢΪ�գ�\n");

		system("pause");

		return ;
	}

	//��ʾ������ϵ����Ϣ
	printf("%10s%10s%10s%10s%10s\n",
		"����","�Ա�","����","�绰","סַ");
	for (i = 0; i < pcon->_sz; i++)
	{
		showinfo(pcon, i);
	}

	system("pause");
}

//	6�����������ϵ����Ϣ
void empty_contact(pContact pcon)
{
	int i = 0;

	assert(pcon);

	memset(pcon, 0, sizeof(Contact));

	pcon->_sz = 0;
	free(pcon->_pdata);
	pcon->_pdata = NULL;

	printf("��ճɹ���\n");

	system("pause");
}

//	7������������������ϵ��
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

	printf("����ɹ���\n");

	display_contact(pcon);
}

//��������Ϊname����
int find_name(pContact pcon)
{
	char name[MAX_NAME] = {0};
	int i = 0;

	printf("�������ϵ������ > ");
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

//��ʾ��i����ϵ����Ϣ
void showinfo(pContact pcon, int i)
{
	printf("%10s", (pcon->_pdata + i)->_name);
	printf("%10s", (pcon->_pdata + i)->_sex);
	printf("%10d", (pcon->_pdata + i)->_age);
	printf("%10s", (pcon->_pdata + i)->_tel);
	printf("%10s\n", (pcon->_pdata + i)->_addr);
}

//�����ռ�����
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