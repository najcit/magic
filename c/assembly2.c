// assembly2.c

#include <stdio.h>

int add(int a, int b)
{
    return a + b;
}

int main(int argc, char **argv)
{
    int a = 10;
    int b = 20;
    int sum = 0;

    // 通过汇编语言的 call 指令调用了 C 语言的 add 函数
    asm(
        "movl %1, %%edi\n"
        "movl %2, %%esi\n"
        "call add\n"
        "movl %%eax, %0"
        : "=r"(sum)
        : "r"(a), "r"(b)
        : "%edi", "%esi");

    printf("The sum of %d and %d is: %d\n", a, b, sum);

    return 0;
}
