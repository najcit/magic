// assembly.c


#include <stdio.h>

int add(int a, int b)
{
	// asm("指令序列":输出列表:输入列表:修改内容);
    asm volatile(            // volatile 修饰来防止被编译器优化
        "addl %%ebx, %%eax;" // 指令序列
        : "=a"(a)            // 输出列表
        : "a"(a), "b"(b)     // 输入列表
        : "memory");         // 修改内容
    return a;
}

int main(int argc, char **argv)
{
    int a = 1, b = 2;
    int result = add(a, b);
    printf("result = %d\n", result);
    return 0;
}