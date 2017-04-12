/*
Copyrights (c) 2016, 西科大8555室石俊涛
All rights resverse

文件名称：
文件标识：
摘    要：模拟printf函数

当前版本：
作    者：石俊涛
完成日期：2016/11/06
*/
/*
va_list arg;
va_start(arg, n);
va_arg(arg, int);
va_end(arg);
*/
#include <stdio.h>
#include <assert.h>
#include <stdarg.h>
#include <string.h>

int m_printf(const char *str, ...)
{
	char *eos = (char *)str;
	int ret = 0;

	va_list ap;
	va_start(ap, str);

	assert(str);

	while (*eos)
	{
		if('%' == *eos)
		{
			int d = 0;
			char c = 0;
			char *s = NULL; 

			eos++;
			
			switch(*eos)
			{
			case 's':
				s = va_arg(ap, char*);
				while(*s)
				{
					putchar(*s);
					s++;
					ret++;
				}
				//不能用puts()->会自动换行
				//不能用putchar()->会只输出首字母
				break;
			case 'c':
			//	c = va_arg(ap, char);
			//	printf("%c", c);
				putchar(va_arg(ap, char));
				ret++;
				break;
			case 'd':
				d = va_arg(ap, int);
				printf("%d", d);
				while(d)
				{
					ret++;
					d /= 10;
				}
				break;
			case '\0':
				putchar('\0');
			default :
				;
				break;
			}
		}
		else
		{
			putchar(*eos);
			ret++;	
		}

		eos++;
	}

	va_end(ap);

	return (ret);
}

int main()
{
	char str1[] = "Hello";
	char str2[] = "bit";
	int num = 200;

	int ret1 = m_printf("第%d行 : %s %c%c%c\n", 100, "hello",'b','i','t');
	int ret2 = m_printf("第%d行 : %s %s\n", num, str1, str2);
	//求解：中文为什么能这样以%c打印出来，而不是%s

	//m_printf(NULL);
	//试验：当传入空指针时。

	m_printf("ret1 = %d\n",ret1);   
	m_printf("ret2 = %d\n",ret2);

	return 0;
}