// example.c

// 生成共享库
// gcc  --share -fPIC example.c -o _example.so

int add(int a, int b)
{
    return a + b;
}
