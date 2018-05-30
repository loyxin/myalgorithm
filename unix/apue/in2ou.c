/*************************************************************************
	> File Name: copy.c
	> Author: loyxin
	> Mail: rafrozenluoxin@gmail.com 
	> Created Time: 2018-03-10 20:09:50
 ************************************************************************/
#include"include/apue.h"
// 输入什么, 在屏幕输出什么
int main(int argc, const char *argv[])
{
	int c;
	while( (c=getc(stdin))!=EOF )
		if(putc(c,stdout)==EOF)//复制文件,并判断是否成功
			err_sys("output error");
	if( ferror(stdin) )
		err_sys("input error");
	exit(0);
	return 0;
}
