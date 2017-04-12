#include <stdio.h>
#include <stdlib.h>

void Output_Multiplication_table(int n);

int main()
{
	int rows = 0;

	printf("rows = ");
	scanf("%d",&rows);

	system("mode con cols=150 lines=100");

	Output_Multiplication_table(rows);

	return 0;

}
void Output_Multiplication_table(int n)
{
	
	int i = 0;
	
	for(i = 1; i <=n; i++)
	{
		int j = 0;

		for(j = 1; j <= i; j++)
		{
			printf("%2d*%-2d=%3d ", j, i, i*j);
		}

		printf("\n");
	}
}
