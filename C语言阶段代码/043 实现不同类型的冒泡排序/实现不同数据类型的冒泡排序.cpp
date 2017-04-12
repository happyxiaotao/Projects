#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Stu
{
	char name[10];
	int age;
}Stu,*pStu;

//����������
int sort_int(const void *elem1, const void *elem2)
{
	return (*(int*)elem1 - *(int*)elem2);
} 

//���ַ�����������
int sort_str(const void *elem1, const void *elem2)
{
	return strcmp((char *)elem1, (char *)elem2);
}


//���ṹ�����ַ�����Ա����
int sort_stu_str(const void *str1, const void *str2)
{
	return strcmp(((pStu)str1)->name,((pStu)str2)->name);
}

//���ṹ�������ͳ�Ա����
int sort_stu_int(const void *str1, const void *str2)
{
	return (((pStu)str1)->age - ((pStu)str2)->age);
}

//��������ռ�����
void Swap(char *str1, char *str2, int n)
{
	int i = 0;

	for (i = 0; i < n; i++)
	{
		char tmp = str1[i];
		str1[i] = str2[i];
		str2[i] = tmp;
	}
}

//MSDN����ԭ��
//void qsort( void *base, size_t num, size_t width, int (__cdecl *compare )(const void *elem1, const void *elem2 ) );
//compare( (void *) elem1, (void *) elem2 );

//�Լ�����ĺ���������˼�룺1��ð������,2������ָ��
void bubble_sort(void *base, int num, int width, int (*compare)(const void*, const void*))
{
	int i = 0;

	for (i = 0; i < num-1; i++)
	{
		int j = 0;

		for (j = 0; j < num-1-i;j++)
		{
			//������Ԫ�ص��׵�ַ�����Լ�����ĺ�����
			if (compare((char*)base+j*width, (char*)base+(j+1)*width) > 0)
			{
				//�����ռ�����
				Swap((char*)base+j*width, (char*)base+(j+1)*width, width);
			}
		}
	}
}

int main()
{
	//��������
	int arr[] = {1,3,5,7,9,0,2,4,6,8};

	int sz = 0;

	//�ַ�������,(ÿ���ַ�����СΪ6)
	char str[][6] = {"wo","shi","hai","zei","wang"};

	//�ṹ������
	Stu stu[3] = {	{"bbb", 10},
					{"aaa", 20},
					{"ccc", 6}};
	int i = 0;

	//�������򣬲����
	sz = sizeof(arr)/sizeof(arr[0]);

	printf("����������\n");
	bubble_sort(arr, sz, sizeof(int), sort_int);

	for (i = 0; i < sz; i++)
	{
		printf("%d ",arr[i]);
	}
	//���ַ�����������,�����
	sz = sizeof(str)/sizeof(str[0]);

	bubble_sort(str, sz, sizeof(char [6]), sort_str);
	
	printf("\n�ַ�������������\n");
	for (i = 0; i < sz; i++)
	{
		printf("%s\n", str[i]);
	}


	//�ṹ���ַ�����Ա���򣬲����
	sz = sizeof(stu)/sizeof(stu[0]);

	bubble_sort(stu, sz, sizeof(stu[0]), sort_stu_str);

	printf("����������\n");
	for (i = 0; i < 3; i++)
	{
		printf("%s,%d\n", stu[i].name, stu[i].age);
	}
	
	//�ṹ�����ͳ�Ա���򣬲����
	sz = sizeof(stu)/sizeof(stu[0]);

	bubble_sort(stu, 3, sizeof(stu[0]), sort_stu_int);

	printf("����������\n");
	for (i = 0; i < sz; i++)
	{
		printf("%s,%d\n", stu[i].name, stu[i].age);
	}

	return 0;
}