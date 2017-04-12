#include <stdio.h>
#include <assert.h>

int m_strlen(const char *src)
{
	int len = 0;

	assert(src != NULL);

	while (*src++)
	{
		len++;
	}
	return len;
}

char * m_replace(char *dest, const char ch, const char* src)
{
	int old_len = m_strlen(dest);
	int new_len = 0;
	int ch_count = 0;
	int src_len = m_strlen(src);
	char *ret = dest;
	char *p_old = NULL;
	char *p_new = NULL;

	assert(dest != NULL);

	while (*dest++)
	{
		if (ch == *(dest-1))
		{
			ch_count++;
		}
	}

	dest = ret;

	new_len = old_len + (src_len-1)*ch_count;

	p_old = dest + old_len - 1;
	p_new = dest + new_len - 1;

	*(p_new+1) = '\0';

	while (p_old < p_new)
	{
		if (ch == *p_old)
		{
			int i = 0;
			for(i = 0; i < src_len; i++)
			{
				*p_new-- = src[src_len-1-i];
			}
			p_old--;
		}
		else
		{
			*p_new-- = *p_old--;
		}
	}
	
	return ret;
}

int main()
{
	char str[30] = "wo shi hai zei wang !";
	printf("原字符串数组是：%s\n",str);
	m_replace(str, ' ', "%20");
	printf("修改后字符串是：%s\n", str);
	return 0;
}
