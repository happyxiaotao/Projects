#include <stdio.h>
int main()  
{  
    int killer = 'A';  
    for(killer = 'A'; killer <= 'D'; ++killer)//���������ASCII ��A-D����ѭ���ͱȽ�  
    {  
        //����ֱ��Ӧÿ���˶�����
        if (3 == ((killer!='A') + (killer=='C') + (killer=='D') + (killer!='D')))  //�������3��ʾ ��������˵���滰  
        {  
            printf("%c������\n",killer);  
	//		break;  
        }  
    }  
    return 0;  
}  