/*************************************************************************
	> File Name: ls.c
	> Author: loyxin
	> Mail: rafrozenluoxin@gmail.com 
	> Created Time: 2018-04-04 20:53:54
 ************************************************************************/

#include"../include/apue.h"
int main(int argc, const char *argv[])
{
	int i;
	struct stat buf;
	char* ptr;
	for(i = 1;i<argc;i++){
		printf("%s: ",argv[i]);
		if(lstat(argv[i],&buf)<0){
			err_ret("lstat error");
			continue;
		}
		if(S_ISREG(buf.st_mode))
			ptr = "regular";
		printf("%s\n",ptr);
	}
	return 0;
}
