/*
第一次代码
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
功能：用%20替换空格
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
/*注意：此处会有两处陷阱：
陷阱1：char *str = "hai zei wang"; 
	原因：str指向常量字符串，不能对其进行修改，不然，程序会崩溃。	
陷阱2：char str[] = "hai zei wang";
	原因：因为没有预留足够大的空间，导致再给数组添加内容时，
	数组空间不够，会对数组以外空间赋值，最终程序崩溃。
*/
	printf("old:%s\n",str);

	replaceSpace(str);

	printf("new:%s\n",str);

	return 0;
}