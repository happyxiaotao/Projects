#include <stdio.h>
#include <stdlib.h>
int main()
{
	int rows = 15;
	int i = 0, j = 0;
	int count = 0;
	//���������СΪrows*��rows��/ 2 = 120
	int Yanghui[120] = {0};

	system("mode con cols=150 lines=100");

	printf("%d���������������ʾ��\n",rows);

	for(i = 0; i < rows; i++)
	{
		for(j = 0; j < rows -1 - i; j++)
		{
			printf("    ");
		}

		for(j = 0; j <= i; j++)
		{
			int left = i*(i+1)/2;//��������������±�
			int right = (i+1)*(i+2)/2-1;//�������ұ������±�
			int last_low = count-i-1;//��һ������������С����
			int last_high = count-i;//��һ�����������д����
			Yanghui[count] = Yanghui[last_low] + Yanghui[last_high];
			Yanghui[left] = Yanghui[right] = 1;//���¸�ֵ������ֵ��Ϊ1
			printf("%4d",Yanghui[count++]);
			printf("    ");
		}
		printf("\n");
	}

	printf("\nһ����%d����\n",count);

	return 0;
}