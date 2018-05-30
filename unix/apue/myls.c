/*************************************************************************
	> File Name: myls.c
	> Author: loyxin
	> Mail: rafrozenluoxin@gmail.com 
	> Created Time: 2018-03-10 17:42:39
 ************************************************************************/

#include "include/apue.h"
#include<dirent.h>
// 实现 ls 的功能
int main(int argc, const char *argv[])
{
	DIR * dp;
	struct dirent* dirp;
	if( argc!=2 )
		err_quit("usage: ls directory name");
	if( (dp=opendir(argv[1]))==NULL )
		err_sys("can't open %s", argv[1]);
	while( (dirp=readdir(dp))!=NULL )
		printf("%s\n",dirp->d_name);

	closedir(dp);
	exit(0);
}
