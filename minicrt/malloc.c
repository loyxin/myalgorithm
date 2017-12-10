//malloc.c

#include "minicrt.h"

typedef struct _heap_header{
    enum{
        // 设置魔数,用于判断
        HEAP_BLOCK_FREE = 0xABABABAB,
        HEAP_BLOCK_USED = 0xCDCDCDCD,
    } type;

    unsigned size;
    struct _heap_header* next;
    struct _heap_header* prev;
} heap_header;

#define ADDR_ADD(a,o) (((char*)(a)) + o)
#define HEADER_SIZE (sizeof(heap_header))

static heap_header* list_head = NULL;

void free(void * ptr)
{
    // 要析构的指针用的地方是可用的,所以要移动头信息
    heap_header* header = (heap_header*) ADDR_ADD(ptr,-HEADER_SIZE);
    if(header->type!=HEAP_BLOCK_USED)
        return;
    // 修改成 free
    header->type = HEAP_BLOCK_FREE;
    // 前一个堆存在,并且也是 free 合并
    if(header->prev != NULL && header->prev->type == HEAP_BLOCK_FREE){
        //merge
        header->prev->next = header->next;
        if(header->next != NULL)
            header->next->prev = header->prev;
        header->prev->size += header->size;

        header = header->prev;
    }
    // 后一个堆存在,并且也是 free 合并
    if(header->next != NULL && header->next->type == HEAP_BLOCK_FREE){
        //merge
        header->size += header->next->size;
        header->next = header->next->next;
    }
    // 由于只可能存在 前后一个堆是 free, 不可能前后两个都是 free, 因为当 前两个 free 的时候 会合并
}

void * malloc(unsigned size){
    heap_header * header;
    if(size == 0)
        return NULL;
    
    header = list_head;
    while(header != 0){
        // 到达可用的堆
        // 有可能可用堆位于 不可用的堆之间
        // 每次只能跨越不可用的堆
        if(header->type == HEAP_BLOCK_USED){
            header = header->next;
            continue;
        }
        // 只有一个空余堆刚好满足,不能拆分
        if(header->size > size + HEADER_SIZE &&
            header->size<=size + HEADER_SIZE*2){
                header->type = HEAP_BLOCK_USED;
            // 返回可用的地方的指针,除去头信息
            return ADDR_ADD(header,HEADER_SIZE);   
            }
        // 可以拆分
        if(header->size>size+HEADER_SIZE*2){
            //split
            heap_header* next = (heap_header*)ADDR_ADD(header,
            size + HEADER_SIZE);
            next->prev = header;
            next->next = header->next;
            next->type = HEAP_BLOCK_FREE;
            next->size = header->size - (size - HEADER_SIZE);
            header->next = next;
            header->size = size + HEADER_SIZE;
            header->type = HEAP_BLOCK_USED;
            // 返回可用的地方的指针,除去头信息
            return ADDR_ADD(header,HEADER_SIZE);
        }
        // 没有找到合适的堆,去查找下一个可用的堆
        header = header->next;
    }
    return NULL;
}

#ifndef WIN32
//linux brk system call
static int brk(void* end_data_segment){
    int ret = 0;
    // brk system call number:45
    // in /usr/include/asm-i386/unistd.h:
    // #define __NR_brk 45
    asm( "movl $45, %%eax  \n\t"
        "movl %1,%%ebx    \n\t"
        "int $0x80 \n\t"
        "movl %%eax,%0 \n\t"
        : "=r"(ret):"m"(end_data_segment) );
}
#endif

#ifdef WIN32
#include <Windows.h>
#endif

int mini_crt_heap_init(){
    void* base = NULL;
    heap_header* header = NULL;
    //32MB heap size
    unsigned heap_size = 32*1024*1024;

    #ifdef WIN32
        base = VirtualAlloc(0,heap_size,MEM_COMMIT |
        MEM_RESERVE,PAGE_READWRITE);
        if(base == NULL)
            return 0;
    #else
            base = (void*)brk(0);
            void * end = ADDR_ADD(base,heap_size);
            end = (void*)brk(end);
            if(!end)
                return 0;
    #endif

    header = (heap_header*)base;
    header->size = heap_size;
    header->type = HEAP_BLOCK_FREE;
    header->next = NULL;
    header->prev = NULL;

    list_head = header;
    return 1;
}
