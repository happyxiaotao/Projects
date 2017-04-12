
#include <stdio.h>
#include <assert.h>

void *my_memmove( void *dest, const void *src, int count )
{
	char *pdest = ( char * )dest;
	char *psrc = ( char * )src;

	assert( dest != NULL );
	assert( src != NULL );

	if ( psrc >= pdest || psrc <= pdest - count )
	{	//从前放
		while ( count )
		{
			*pdest = *psrc;

			++pdest;
			++psrc;

			--count;
		}
	}
	else
	{	//从后放
		pdest += count-1;
		psrc += count-1;

		while ( count )
		{
			*pdest = *psrc;

			--pdest;
			--psrc;
			
			--count;
		}
	}

	return ( dest );
}
int main()
{
	char str1[] = "shijuntao";
	int arr[] = { 1, 2, 3, 4, 5 };
	int sz = sizeof( arr )/sizeof( *arr );
	int i = 0;
	my_memmove( str1+2, str1, 3*sizeof( char ) );
	my_memmove( arr+1, arr, 2*sizeof( int ) );
	
	printf( "%s\n", str1 ); 
	for ( i = 0; i < sz; i++ )
	{
		printf( "%d ", arr[i] );
	}
	return ( 0 );
}
