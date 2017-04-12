#include <stdio.h>
#include <assert.h>

char* m_strcpy(char* dest, const char* src)
{
	char* ret = *dest;

	assert(dest != NULL);
	assert(src != NULL);

	while(*dest++ = *src++)
		;

	return ret;
}

int main()
{
	char str[15];

	m_strcpy(str, "hai zei wang");

	printf("%s\n", str);

	return 0;	
}