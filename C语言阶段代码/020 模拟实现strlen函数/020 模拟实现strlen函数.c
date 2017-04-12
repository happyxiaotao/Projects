#include <stdio.h>
#include <assert.h>
/*一般实现
int m_strlen(const char* src)
{
	int count = 0;

	assert(src != NULL);

	while (*src++)
	{
		++count;
	}

	return count;
}
*/
/*递归实现
int m_strlen(const char* src)
{
	assert(src);
	if(*src == '\0')
		return 0;
	else
		return (1 + m_strlen(src+1));
}*/
/*库函数实现*/
int m_strlen(const char *dest)
{
	const char *eos = dest;
	assert(dest);
	while(*eos++)
	{
		;
	}

	return eos-dest-1;
}
int main()
{
	char str[] = "shijuntao";

	int count = m_strlen(str);

	printf("count = %d\n",count);

	return 0;
}