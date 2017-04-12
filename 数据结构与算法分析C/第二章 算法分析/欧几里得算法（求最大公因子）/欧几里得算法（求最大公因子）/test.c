#include <stdio.h>

int Gcd(unsigned int m, unsigned int n)
{
	unsigned int rem = 0;
	
	while (n)
	{
		rem = m%n;
		m = n;
		n = rem;
	}

	return m;
}

double ProbabilityOfEachElement(unsigned int m)
{	
	int total = 0;
	int count = 0;
	unsigned int i = 0;

	for (i = 1; i <= m; ++i)
	{
		unsigned int j = 0;

		for (j = i; j <= m; ++j)
		{	
			++total;

			if (1 == Gcd(i, j))
				++count;
		}
	}

	return (double)count/total;
}

int main()
{	
	//int gcd = Gcd(3, 9);
	//printf("gcd = %d\n", gcd);
	//gcd = Gcd(3, 10);
	//printf("gcd = %d\n", gcd);
	//gcd = Gcd(7, 10);
	//printf("gcd = %d\n", gcd);
	//gcd = Gcd(17, 10);
	//printf("gcd = %d\n", gcd);

	int i = 0;
	for (i = 1; i < 10; ++i)
		printf("The probability of each element is %f\n", ProbabilityOfEachElement(i));
	return 0;
}