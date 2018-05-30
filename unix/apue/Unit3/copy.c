/*************************************************************************
	> File Name: copy.c
	> Author: loyxin
	> Mail: rafrozenluoxin@gmail.com 
	> Created Time: 2018-04-03 17:51:01
 ************************************************************************/

#include"../include/apue.h"

#define BUFFSIZE 4096
int main(int argc, const char *argv[])
{
	int n;
	char buf[BUFFSIZE];

	while( (n = read(STDIN_FILENO, buf, BUFFSIZE) )>0 )
		if( write(STDOUT_FILENO, buf, n)!=n )
			err_sys("write_error");
	if( n<0 )
		err_sys("read error");

	return 0;
}
