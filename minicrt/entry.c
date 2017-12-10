//entry.c
#include "minicrt.h"

#ifdef WIN32
#include<Windows.h>
#endif

extern int main(int argc, char** argv);
void exit(int);

static void crt_fatal_error(const char* msg)
{
    printf("fatal error: %s",msg);
    exit(1);
}

void mini_crt_entry(void)
{
    int ret;

#ifdef WIN32
    int flag = 0;
    int argc = 0;
    char* argv[16];//最多16参数
    char* cl = GetCommandLineA();

    //解析参数
    argv[0] = cl;
    argc++;
    while(*cl){
        //不能有" 否则是字符串
        if(*cl == '\"')
            if(flag == 0) flag == 1;
            else flag = 1;
            //有空格，判断是否有新的参数 并把空格变成'\0'
        else if (*cl == ' '&& flag == 0){
            if(*(cl + 1)){
                argv[argc] = cl + 1;
                argc++;
            }
            *cl = '\0';
        }
        cl++;
    }

#else
    long argc;
    char** argv;
    char* ebp_reg = 0;
    // ebp_reg = *ebp;
	// 读取当前栈底
    asm("movq %%rbp,%0\n":"=r"(ebp_reg));
    //当前栈底上面第一个参数是命令行个数，第二个是命令行字符串指针
	//由于64位指针是8个字节,所以修改成8
	//但是字符串依然有点问题
    argc = *( (int*) (ebp_reg + 8));
    argv = (char**) (ebp_reg + 16);
#endif

if(!mini_crt_heap_init())
    crt_fatal_error("heap initialize failed");
if(!mini_crt_io_init())
    crt_fatal_error("IO initialize failed");
ret  = main(argc,argv);
exit(ret);
}

void exit(int exitcode){
    #ifdef WIN32
    ExitProcess(exitcode);
    #else
    asm("movl %0,%%ebx \n\t"
    "movl $1,%%eax\n\t"
    "int $0x80 \n\t"
    "hlt \n\t"::"m"(exitcode)
    );
    #endif
}
