#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
int main()
{
	char arr[] = "created in China !!";
	char temp[32] = {0};
	int i = 0;
	int len = strlen(arr);
	int right = len-1, left = 0; 

	while(i<len)
	{
		temp[i] = '#';
		i++;
	}

	puts(temp);

	while(right >= left)
	{
		Sleep(1000);
		printf("\a");
		temp[right] = arr[right];
		temp[left] = arr[left];
		puts(temp);
		right--;
		left++;
	}

	system("pause");
	return 0;
}