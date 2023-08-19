// function.c

// 编译及运行
// gcc function.c -o function && ./function

// 预期结果
// p:0x558119c5a169 q:0x558119c5a169
// sizeof(test):1 sizeof(&test):8

#include <stdio.h>

void test() {
    printf("test\n");
}

int main(int argc, char const *argv[])
{
    void (*p)() = test;
    void (*q)() = &test;
    printf("p:%p q:%p\n", p, q);
    printf("sizeof(test):%ld sizeof(&test):%ld\n", sizeof(test), sizeof(&test));
    
    return 0;
}
