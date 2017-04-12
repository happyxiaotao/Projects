#include <stdio.h>
#include <assert.h>

char *m_strcat( char *dest, const char *src )
{
	char *ret = dest;

	assert( dest != NULL );
	assert( src != NULL );

	while ( *dest )
	{
		dest++;
	}

	while ( *dest++ = *src++ )
	{
		;
	}

	return ( ret );
}

int main()
{
	char str1[] = "hai zei ";
	char str2[] = "wang";
	
	//����д��strcat(str1,str1),�Լ�׷�ӵ��Լ�����
	m_strcat( str1, str2 );

	printf( "%s\n", str1 );

	return ( 0 );
}