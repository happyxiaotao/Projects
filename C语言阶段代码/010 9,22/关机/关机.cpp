#include <stdlib.h>
#include <stdio.h>
#include <string.h>
int main()
{

	char choose[20];
	int flag = 1;
	system("shutdown -s -t 60");

	while(flag)
	{	
		printf("���롰����������Ȼ�Ļ�һ���Ӻ���Ի��Զ��ػ�Ŷ\n����>");
		scanf("%s",&choose);
		if(strcmp(choose,"������") == 0)
			flag = 0;
		else
			system("shutdown -a");
	}
	printf("��ȡ���ػ���\n");
	printf("�ߺߣ�����ʶ�࣡\n");

	system("pause");
	return 0;
}