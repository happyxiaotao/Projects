/*
Copyrights (c) 2016, 西科大8555室石俊涛
All rights resverse

文件名称：
文件标识：
摘    要：模拟实现strsrt函数

当前版本：
作    者：石俊涛
完成日期：2016/11/06
*/

#include <string.h>
#include <stdio.h>
#include <assert.h>

char *my_strstr( const char *str1, const char *str2 )
{
	char *cp = ( char * )str1;

	assert( str1 != NULL );
	assert( str2 != NULL );

	while ( !*str2 )
	{
		return ( cp );
	}

	while ( *cp )
	{
		char *p1 = cp;
		char *p2 = ( char * )str2;

		while ( (*p1 == *p2) && *p2)
		{
			++p1;
			++p2;
		}

		if ( !*p2 )
		{
			return ( cp );
		}

		++cp;
	}

	return ( NULL );
}

int main()
{
	char dest[] = "shijuntao";
	char src[] = "junt";

	char *ret = strstr( dest, src );

	if ( ret )
	{
		printf( "index = %d\n", ( ret - dest ) );
	}
	else
	{
		printf( "Cannot find !\n" );
	}

	return ( 0 );
}

