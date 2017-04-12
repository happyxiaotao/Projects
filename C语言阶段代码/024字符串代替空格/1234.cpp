#include <iostream>
using namespace std;
//length为系统规定字符串输出的最大长度，固定为一个常数
class Solution {
public:
    void replaceSpace(char *str, int length){
        int blankNumber = 0;//空格的数量
        int oldstringLen;//记录原字符串的长度
        //首先遍历原字符串，找出字符串的长度以及其中的空格数量
        for (oldstringLen = 0; str[oldstringLen] != '\0'; oldstringLen++){

            if (str[oldstringLen] == ' ')
                blankNumber++;
        }

        //根据原字符串的长度和空格的数量我们可以求出最后新字符串的长度
        int newstringLen = oldstringLen + blankNumber * 2;//新字符串的长度
        if (newstringLen>length)
            return;
        str[newstringLen] = '\0';//此行很重要，因为原字符串最后一个字符为'\0'

        //设置两个指针point1和point2分别指向原字符串和新字符串的末尾位置
        int point1 = oldstringLen - 1, point2 = newstringLen - 1;//因为'\0'已经手工加到最后新串的最后一个字符，所以减1咯

        while (point1 >= 0 && point2>point1){//两指针相同时，跳出循环

            if (str[point1] == ' '){//如果point1指向为空格，那么从point2开始赋值“02%”
                str[point2--] = '0';
                str[point2--] = '2';
                str[point2--] = '%';

            }
            else    //如果point1指向内容不为空格，那么将内容赋值给point2指向的位置
                str[point2--] = str[point1];

            point1--;//不管是if还是else都要把point1前移,为了下一次的执行

        }


    }
};