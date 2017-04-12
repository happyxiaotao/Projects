
#include <stdio.h>
#include <assert.h>

int my_strcmp( const char *dest, const char *src )
{
	int ret = 0;

	assert( dest != NULL );
	assert( src != NULL );

	while ( !(ret = *dest - *src) && *src )
	{
		++dest;
		++src;
	}

	if ( ret > 0 )
	{
		return ( 1 );
	}
	else if ( ret < 0 )
	{
		return ( -1 );
	}

	return ( 0 );
}

int main()
{
	char dest[] = "hai zei wang";

	char src1[] = "";
	char src2[] = "hai zei wang !";
	char src3[] = "hai zei wang";

	int ret1 = my_strcmp( dest, src1 );
	int ret2 = my_strcmp( dest, src2 );
	int ret3 = my_strcmp( dest, src3 );

	printf( "ret1 = %d\n", ret1 );
	printf( "ret2 = %d\n", ret2 );
	printf( "ret3 = %d\n", ret3 );

	return ( 0 );
}
