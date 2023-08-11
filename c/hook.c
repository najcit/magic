// 文件名: hook.c

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>

#define PAGE_START(x, pagesize) ((unsigned long)(x) & ~((pagesize)-1))

#ifndef DBG_SWITCH
#define DBG_SWITCH 0  // 调试开关 0 => 关 1 => 开 
#endif // DBG_SWITCH
#define printf DBG_SWITCH && printf

static int adjust_protect_memory_permissions(void *func, int permissions, int pagesize)
{
    if (pagesize <= 0)
    {
        pagesize = getpagesize();
    }
    if (mprotect((void *)PAGE_START(func, pagesize), pagesize, permissions) < 0)
    {
        printf("mprotect error");
        return -1;
    }
    return 0;
}

void *install_hook(void *old_func, void *new_func)
{
    if (!old_func || !new_func) {
        return NULL;
    }

    int pagesize = getpagesize();
    if (adjust_protect_memory_permissions(old_func, PROT_READ | PROT_WRITE | PROT_EXEC, pagesize) < 0)
    {
        return NULL;
    }

    unsigned char *old_func_p = (unsigned char *)old_func;
    unsigned char *new_func_p = (unsigned char *)new_func;
    unsigned char *handler = (unsigned char *)malloc(5);
    if (!handler)
    {
        return NULL;
    }
    handler[0] = old_func_p[0];
    *(int *)(handler + 1) = *(int *)(old_func_p + 1);

    printf("*** hook engine: buf: 0x%02x\n", *handler);
    printf("*** hook engine: buf: 0x%08x\n", *(int *)(handler + 1));
    int offset = new_func_p - (old_func_p + 5);
    old_func_p[0] = 0xE9;
    printf("*** hook engine: (1) old_func_p: 0x%08x\n", *(int *)(old_func_p + 1));
    *(int *)(old_func_p + 1) = offset;
    printf("*** hook engine: (2) old_func_p: 0x%08x\n", *(int *)(old_func_p + 1));

    adjust_protect_memory_permissions(old_func, PROT_READ | PROT_EXEC, pagesize);
    return handler;
}

int uninstall_hook(void *old_func, void *handler)
{
    if (!old_func || !handler) {
        return -1;
    }
    
    int pagesize = getpagesize();
    if (adjust_protect_memory_permissions(old_func, PROT_READ | PROT_WRITE | PROT_EXEC, pagesize) < 0)
    {
        return -1;
    }

    unsigned char *old_func_p = (unsigned char *)old_func;
    unsigned char *handler_p = (unsigned char *)handler;
    old_func_p[0] = handler_p[0];
    *(int *)(old_func_p + 1) = *(int *)(handler_p + 1);
    free(handler);
    handler = NULL;

    adjust_protect_memory_permissions(old_func, PROT_READ | PROT_EXEC, pagesize);
    return 0;
}

int hook(void *main_func, void *old_func, void *new_func)
{
    int pagesize = getpagesize();
    if (adjust_protect_memory_permissions(old_func, PROT_READ | PROT_WRITE | PROT_EXEC, pagesize) < 0)
    {
        return -1;
    }

    unsigned char *p = (unsigned char *)main_func;
    unsigned char *old_func_p = (unsigned char *)old_func;
    unsigned char *new_func_p = (unsigned char *)new_func;
    if (!p || !old_func_p || !new_func_p) {
        return -1;
    }

    printf("*** hook engine: start patch old func: %p\n", old_func_p);
    for (int i = 0; i < pagesize; ++i, ++p)
    {
        if (p[0] == 0xe8)
        {
            printf("*** hook engine: opcode: 0x%02x\n", p[0]);
            int offset = *(int *)(p + 1);
            printf("*** hook engine: offset: 0x%08x\n", offset);

            unsigned char *func = p + 5 + offset;
            printf("*** hook engine: func: %p old func: %p\n", func, old_func);
            if (func == old_func_p)
            {
                int offset = new_func_p - (p + 5);
                printf("*** hook engine: new func offset: 0x%08x\n", offset);
                printf("*** hook engine: (1) p: 0x%08x\n", *(int *)(p + 1));
                *(int *)(p + 1) = offset;
                printf("*** hook engine: (2) p: 0x%08x\n", *(int *)(p + 1));
            }
        }
    }
    printf("*** hook engine: have pachted new func: %p.\n", new_func_p);

    adjust_protect_memory_permissions(main_func, PROT_READ | PROT_EXEC, pagesize);

    return 0;
}

int unhook(void *main_func, void *old_func, void *new_func)
{
    return hook(main_func, new_func, old_func);
}

#undef printf

void test(int x)
{
    printf("%s: %d\n", __FUNCTION__, x);
}

void test_hooker(int x)
{
    printf("%s: %d\n", __FUNCTION__, x);
}

int main(int argc, const char *argv[])
{
    // inline hook
    void *handler = install_hook(&test, &test_hooker);

    test(0);

    uninstall_hook(&test, handler);

    test(0);

    // offset hook
    hook(&main, &test, &test_hooker);

    test(1);

    unhook(&main, &test, &test_hooker);

    test(1);

    return 0;
}