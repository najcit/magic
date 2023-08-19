// example.c

// 编译生成动态链接库
// gcc -fPIC -shared example.c -o example.so

#include <stdio.h>
#include <stdlib.h>

int add(int a, int b)
{
    return a + b;
}
