#include <stdio.h>
#include <string,h>
//Horner·¨Ôò
long int Horner(long int X, const int A[], unsigned int N)
{
	long int Poly = 0;
	unsigned int i = 0;

	for (i = N; i >= 0; --i)
		Poly = X*Poly + A[i];

	return Poly;
}

int main()
{
	return 0;
}
