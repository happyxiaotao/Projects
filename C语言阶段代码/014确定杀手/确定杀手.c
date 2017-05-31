#include <stdio.h>
int main()  
{  
    int killer = 'A';  
    for(killer = 'A'; killer <= 'D'; ++killer)//巧妙地利用ASCII 从A-D进行循环和比较  
    {  
        //下面分别对应每个人都供词
        if (3 == ((killer!='A') + (killer=='C') + (killer=='D') + (killer!='D')))  //这里等于3表示 有三个人说了真话  
        {  
            printf("%c是凶手\n",killer);  
	//		break;  
        }  
    }  
    return 0;  
}  