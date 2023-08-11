// 文件名：variable_para.c

#include <stdio.h>
#include <stdarg.h>

// 该方式计算函数参数个数，会有一个最大数限制，以下的版本是最多 64 个参数
// 如果要修改限制可以修改ARG_N_M及ARG_N_RESQ对应的参数及数据个数
#define ARG_N(...) ARG_N_(0, ##__VA_ARGS__, ARG_N_RESQ)

#define ARG_N_(...) ARG_N_M(__VA_ARGS__)

#define ARG_N_M(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10,      \
                _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, \
                _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, \
                _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, \
                _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, \
                _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, \
                _61, _62, _63, N, ...) N

#define ARG_N_RESQ 63, 62, 61, 60,                         \
                   59, 58, 57, 56, 55, 54, 53, 52, 51, 50, \
                   49, 48, 47, 46, 45, 44, 43, 42, 41, 40, \
                   39, 38, 37, 36, 35, 34, 33, 32, 31, 30, \
                   29, 28, 27, 26, 25, 24, 23, 22, 21, 20, \
                   19, 18, 17, 16, 15, 14, 13, 12, 11, 10, \
                   9, 8, 7, 6, 5, 4, 3, 2, 1, 0

#define INFO(...) myinfo(ARG_N(__VA_ARGS__), ##__VA_ARGS__)

// 目标函数
int info(int a, char *b, int c, int d)
{
    printf("a: %d b: %s c: %d d: %d\n", a, b, c, d);
}

// 适配函数, 通过传入的参数的个数不同，来补充参数
#define ARG_1 0
#define ARG_2 "test"
#define ARG_3 2
#define ARG_4 3
int myinfo(int argc, ...)
{
    int a = ARG_1;
    char *b = ARG_2;
    int c = ARG_3;
    int d = ARG_4;
    va_list argptr;
    va_start(argptr, argc);
    if (argc >= 4)
    {
        // 如果提供过多参数，则自动忽略
        a = va_arg(argptr, int);
        b = va_arg(argptr, char *);
        c = va_arg(argptr, int);
        d = va_arg(argptr, int);
    }
    else if (argc == 3)
    {
        a = va_arg(argptr, int);
        b = va_arg(argptr, char *);
        c = va_arg(argptr, int);
    }
    else if (argc == 2)
    {
        a = va_arg(argptr, int);
        b = va_arg(argptr, char *);
    }
    else if (argc == 1)
    {
        a = va_arg(argptr, int);
    }
    va_end(argptr);
    return info(a, b, c, d);
}

#define DEFAULT_DEBUG "This is default debug (%s:%u)\n", __FILE__, __LINE__
#define DEBUG(...) #__VA_ARGS__[0] ? myprintf(#__VA_ARGS__, ##__VA_ARGS__) : myprintf(#__VA_ARGS__, DEFAULT_DEBUG)
int myprintf(const char *flag, ...)
{
    int cnt;
    va_list argptr;
    va_start(argptr, flag);
    char *format = va_arg(argptr, char *);
    cnt = vprintf(format, argptr);
    va_end(argptr);
    return cnt;
}

int main(int argc, char const *argv[])
{
    INFO();
    INFO(10);
    INFO(10, "info");
    INFO(10, "info", 8);
    INFO(10, "info", 8, 7);
    INFO(10, "info", 8, 7, 6);

    DEBUG();
    DEBUG("你好%d\n", ARG_N(1, 2));
    DEBUG("%d\n", 123);
    DEBUG("%d %s %f\n", 123, "test", 1.2);
    DEBUG("%d %s %f %x\n", 123, "test", 1.2, 0x1234);
    DEBUG("%d %s %f %x %c\n", 123, "test", 1.2, 0x1234, 78);
    DEBUG("%d %s %f %x %c %p\n", 123, "test", 1.2, 0x1234, 78, 56789);

    return 0;
}
