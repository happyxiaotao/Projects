#include <iostream>
using namespace std;
//lengthΪϵͳ�涨�ַ����������󳤶ȣ��̶�Ϊһ������
class Solution {
public:
    void replaceSpace(char *str, int length){
        int blankNumber = 0;//�ո������
        int oldstringLen;//��¼ԭ�ַ����ĳ���
        //���ȱ���ԭ�ַ������ҳ��ַ����ĳ����Լ����еĿո�����
        for (oldstringLen = 0; str[oldstringLen] != '\0'; oldstringLen++){

            if (str[oldstringLen] == ' ')
                blankNumber++;
        }

        //����ԭ�ַ����ĳ��ȺͿո���������ǿ������������ַ����ĳ���
        int newstringLen = oldstringLen + blankNumber * 2;//���ַ����ĳ���
        if (newstringLen>length)
            return;
        str[newstringLen] = '\0';//���к���Ҫ����Ϊԭ�ַ������һ���ַ�Ϊ'\0'

        //��������ָ��point1��point2�ֱ�ָ��ԭ�ַ��������ַ�����ĩβλ��
        int point1 = oldstringLen - 1, point2 = newstringLen - 1;//��Ϊ'\0'�Ѿ��ֹ��ӵ�����´������һ���ַ������Լ�1��

        while (point1 >= 0 && point2>point1){//��ָ����ͬʱ������ѭ��

            if (str[point1] == ' '){//���point1ָ��Ϊ�ո���ô��point2��ʼ��ֵ��02%��
                str[point2--] = '0';
                str[point2--] = '2';
                str[point2--] = '%';

            }
            else    //���point1ָ�����ݲ�Ϊ�ո���ô�����ݸ�ֵ��point2ָ���λ��
                str[point2--] = str[point1];

            point1--;//������if����else��Ҫ��point1ǰ��,Ϊ����һ�ε�ִ��

        }


    }
};