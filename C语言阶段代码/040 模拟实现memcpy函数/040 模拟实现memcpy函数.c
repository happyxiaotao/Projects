#include <stdio.h>
#include <assert.h>

void *my_memcpy( void *dest, const void *src, int count )
{
	char *pdest = ( char * )dest;
	char *psrc = ( char * )src;

	assert( dest != NULL );
	assert( src != NULL );

	while ( count )
	{
		*pdest = *psrc;

		++pdest;
		++psrc;

		--count;
	}

	return ( dest );
}

int main()
{
	char s1[] = "hai zei wang";
	char s2[] = "shi jun tao";
	
	int arr1[] = { 2, 3, 1 };
	int arr2[] = { 6, 4, 5 ,10 };
	int i = 0;

	my_memcpy( s1, s2 , strlen(s2)+1 );
	my_memcpy( arr1, arr2 , sizeof(arr2)/sizeof(*arr2)*sizeof(int) );

	printf( "%s\n", s1 );

	for (; i < sizeof(arr2)/sizeof(*arr2); ++i )
	{
		printf( "%d ", arr1[i] );
	}

	return ( 0 );
}
