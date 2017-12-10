
#include "minicrt.h"


int main(int argc,char *argv[])
{
	char buf[] = "test ty\n";
printf("hello world\n");
printf("%s\n", buf);
printf("%d\n", argc);
printf("%d\n",*( argv[0])) ;
return 0; 
}
