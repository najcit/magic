// 文件名: backtrace.c

#include <execinfo.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>

#define FRAME_SIZE 100
void dump(int signum) {
    printf("signum: %d\n", signum);
    const int size = FRAME_SIZE;
    void *buffer[size];
    int stack_size = backtrace(buffer, size);

    // 打印信息到终端
    char **stacktrace = backtrace_symbols(buffer, stack_size);
    if (stacktrace) {
        for (int i = 0; i < stack_size; ++i) {
            printf("%s\n", stacktrace[i]);
        }
        free(stacktrace);
    }
    
    // 保存信息到文件
    char core_name[64] = {};
    snprintf(core_name, 64, "core.%d", getpid());
    int fd = open(core_name, 'w');
    if (fd) {
        backtrace_symbols_fd(buffer, stack_size, fd);
        close(fd);
    }
    
    exit(0);
} 

void test1() {
    // 模拟一个 SIGSEGV 信号
    int *a = NULL;
    *a = 1;
}

void test2() {
    test1();
}

void test3() {
    test2();
}

int main(int argc, char const *argv[])
{
    signal(SIGSEGV, dump);
    test3();
    return 0;
}
