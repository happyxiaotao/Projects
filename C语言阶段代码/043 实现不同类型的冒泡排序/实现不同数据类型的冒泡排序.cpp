#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Stu
{
	char name[10];
	int age;
}Stu,*pStu;

//给整型排序
int sort_int(const void *elem1, const void *elem2)
{
	return (*(int*)elem1 - *(int*)elem2);
} 

//给字符串数组排序
int sort_str(const void *elem1, const void *elem2)
{
	return strcmp((char *)elem1, (char *)elem2);
}


//给结构体中字符串成员排序
int sort_stu_str(const void *str1, const void *str2)
{
	return strcmp(((pStu)str1)->name,((pStu)str2)->name);
}

//给结构体中整型成员排序
int sort_stu_int(const void *str1, const void *str2)
{
	return (((pStu)str1)->age - ((pStu)str2)->age);
}

//交换两块空间内容
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

//MSDN函数原型
//void qsort( void *base, size_t num, size_t width, int (__cdecl *compare )(const void *elem1, const void *elem2 ) );
//compare( (void *) elem1, (void *) elem2 );

//自己定义的函数，利用思想：1，冒泡排序,2，函数指针
void bubble_sort(void *base, int num, int width, int (*compare)(const void*, const void*))
{
	int i = 0;

	for (i = 0; i < num-1; i++)
	{
		int j = 0;

		for (j = 0; j < num-1-i;j++)
		{
			//将两个元素的首地址传给自己定义的函数。
			if (compare((char*)base+j*width, (char*)base+(j+1)*width) > 0)
			{
				//交换空间内容
				Swap((char*)base+j*width, (char*)base+(j+1)*width, width);
			}
		}
	}
}

int main()
{
	//整型例子
	int arr[] = {1,3,5,7,9,0,2,4,6,8};

	int sz = 0;

	//字符串例子,(每个字符串大小为6)
	char str[][6] = {"wo","shi","hai","zei","wang"};

	//结构体例子
	Stu stu[3] = {	{"bbb", 10},
					{"aaa", 20},
					{"ccc", 6}};
	int i = 0;

	//整型排序，并输出
	sz = sizeof(arr)/sizeof(arr[0]);

	printf("整型排序结果\n");
	bubble_sort(arr, sz, sizeof(int), sort_int);

	for (i = 0; i < sz; i++)
	{
		printf("%d ",arr[i]);
	}
	//给字符串数组排序,并输出
	sz = sizeof(str)/sizeof(str[0]);

	bubble_sort(str, sz, sizeof(char [6]), sort_str);
	
	printf("\n字符串数组排序结果\n");
	for (i = 0; i < sz; i++)
	{
		printf("%s\n", str[i]);
	}


	//结构体字符串成员排序，并输出
	sz = sizeof(stu)/sizeof(stu[0]);

	bubble_sort(stu, sz, sizeof(stu[0]), sort_stu_str);

	printf("按名字排序\n");
	for (i = 0; i < 3; i++)
	{
		printf("%s,%d\n", stu[i].name, stu[i].age);
	}
	
	//结构体整型成员排序，并输出
	sz = sizeof(stu)/sizeof(stu[0]);

	bubble_sort(stu, 3, sizeof(stu[0]), sort_stu_int);

	printf("按年龄排序\n");
	for (i = 0; i < sz; i++)
	{
		printf("%s,%d\n", stu[i].name, stu[i].age);
	}

	return 0;
}