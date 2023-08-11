// 文件名: tricks.c

#include <stdio.h>
#include <stdlib.h>

// 日志打印
#define LOG(level, format, ...) printf("[%s] <%s> (%s:%d) " format "\n", #level, __FUNCTION__, __FILE__, __LINE__, ##__VA_ARGS__)
#define LOGD(...) LOG(DEBUG, __VA_ARGS__)
#define LOGI(...) LOG(INFO, __VA_ARGS__)
#define LOGW(...) LOG(WARNING, __VA_ARGS__)
#define LOGE(...) LOG(ERROR, __VA_ARGS__)
#define LOGF(...) LOG(FATAL, __VA_ARGS__); abort()

// 打印变量名
#define PRINT_HEX(var) printf("%s: 0x%08x\n", #var, var);

// 获取数组大小
#define ARRAR_SIZE(arr) (sizeof(arr) / sizeof(*arr))

// 依赖已有变量定义新变量
#define var(left, right) __typeof__(right) left = (right)

// 获取结构体成员偏移
#define offsetof(type, member) ((size_t)(&((type *)0)->member))

// 获取较小值
#define MIN(A,B) ({ __typeof__(A) __a = (A); __typeof__(B) __b = (B); __a < __b ? __a : __b; })

// 该方式计算函数参数个数，可能会有 -Wint-conversion 告警
#define ARG_SIZE(...) (sizeof((int[]){0, ##__VA_ARGS__}) / sizeof(int) - 1)

// 该方式计算函数参数个数，会有一个最大数限制，以下的版本是最多 64 个参数
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

int main(int argc, char const *argv[])
{
    LOGD("Test log var: %d", 1234);

    int flag = 0xaabbccdd;
    PRINT_HEX(flag);

    int array[5] = {1, 2, 3, 4, 5};
    LOGI("ARRAR_SIZE(array): %lu", ARRAR_SIZE(array));

    typedef struct
    {
        int a;
    } A;
    A a = {15};
    var(b, a); 
    PRINT_HEX(b.a);
    var(s, 1); 
    PRINT_HEX(s);

    double xx = 1.0;
    double yy = MIN(xx++, 1.5);
    printf("xx=%f, yy=%f\n", xx, yy);

    typedef struct S
    {
        char a;
        int b;
        double c;
    } S;
    LOGI("offsetof(S, c): %ld", offsetof(S, c));

    LOGI("ARG_SIZE(...): %ld", ARG_SIZE(1, 2, 3, 4));

    LOGI("ARG_N(...): %d", ARG_N(1, 2, 3, 4));

    return 0;
}
