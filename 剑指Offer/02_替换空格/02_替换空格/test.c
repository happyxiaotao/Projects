/*
��һ�δ���
int i = 0;
int SpaceCount = 0;
int oldlen = strlen(pstr);
int newlen = oldlen;

assert(pstr);

for (; i < oldlen; i++)
{
	if (' ' == pstr[i])
		SpaceCount++;
}
newlen = oldlen+SpaceCount*2;
while (newlen > oldlen)
{
	if (' ' == pstr[oldlen])
	{
		pstr[newlen--] = '0';
		pstr[newlen--] = '2';
		pstr[newlen--] = '%';
	}
	else
	{
		pstr[newlen--] = pstr[oldlen];
	}
	oldlen--;
}*/

/*
���ܣ���%20�滻�ո�
*/
#include <stdio.h>
#include <string.h>
#include <assert.h>

void replaceSpace(char* pstr)
{	
	int i = 0;
	int count = 0;
	int oldlen = 0;
	int newlen = 0;
	char *before = NULL;
	char *behind = NULL;

	assert(NULL != pstr);

	while (*(pstr+i))
	{
		oldlen++;

		if (' ' == *(pstr+i))
			count++;

		i++;
	}
	newlen = oldlen + count*2;
	before = pstr+oldlen;
	behind = pstr+newlen;

	while (behind > before)
	{
		if (' ' == *before)
		{
			*(behind--) = '0';
			*(behind--) = '2';
			*(behind--) = '%';
		}
		else
		{
			*(behind--) = *(before);
		}
		before--;
	}
}
int main()
{

	char str[20] = "hai zei wang"; 
/*ע�⣺�˴������������壺
����1��char *str = "hai zei wang"; 
	ԭ��strָ�����ַ��������ܶ�������޸ģ���Ȼ������������	
����2��char str[] = "hai zei wang";
	ԭ����Ϊû��Ԥ���㹻��Ŀռ䣬�����ٸ������������ʱ��
	����ռ䲻���������������ռ丳ֵ�����ճ��������
*/
	printf("old:%s\n",str);

	replaceSpace(str);

	printf("new:%s\n",str);

	return 0;
}