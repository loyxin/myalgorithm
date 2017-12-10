//string.c
#include "minicrt.h"
//该函数作用是 把 n 转换相应进制 radix 的数，保存在 str
char* itoa(int n,char* str,int radix)
{
	char digit[]	="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char* p	= str;
	char* head = str;
    //所有加起来只有10+26=36个，所有最多36位进制0最小二进制
	if (!p || radix < 2 || radix > 36)
	{
		return p;
	}
    // 如果是负数，只是转换 10 进制的负数
	if (radix != 10 && n < 0)
	{
		return p;
	}
    // 避免下面的 while 循环
	if (n == 0)
	{
		*p++ = '0';
		*p = 0;
		return p;
	}
    // 如果是负数，只是转换 10 进制的负数
	if (radix == 10 && n < 0)
	{
		*p++ = '-';
		n = -n;
	}

	while (n)
	{
		*p++ = digit[ n % radix];
		n /= radix;
	}
    // 跳出循环时，进制转换的算法，补齐 0
	*p = 0;
    // 反向读取才是真正的可读的数
	for (--p; head < p; ++head,--p)
	{
		char temp = *head;
		*head = *p;
		*p = temp;
	}

	return str;
}

int strcmp(const char* src, const char* dst)
{
	int ret	= 0;
	unsigned char* p1 = (unsigned char*)src;
	unsigned char* p2 = (unsigned char*)dst;

	while(!(ret = *p1 - *p2)&&*p2)
		++p1,++p2;
	if (ret < 0)
	{
		ret	= -1;
	}
	else if (ret > 0)
	{
		ret	= 1;
	}

	return (ret);
}

char * strcpy(char* dest, const char* src)
{
	char* ret = dest;
	while(*src)
	{
		*dest++ = *src++;
	}
	*dest	= '\0';
	return ret;

}

unsigned strlen(const char* str)
{
	int cnt	= 0;
	if(!str)
		return 0;
	for (;*str != '\0';++str)
	{
		++cnt;
	}

	return cnt;
}