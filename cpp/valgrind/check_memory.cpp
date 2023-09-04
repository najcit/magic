// check_memory.cpp

// 编译程序
// g++ check_memory.cpp -o check_memory -g

// 运行程序
// valgrind --leak-check=full --track-origins=yes -s ./check_memory
//  cg_annotate cachegrind.out.*

// 程序输出
// ==25448== Memcheck, a memory error detector
// ==25448== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
// ==25448== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
// ==25448== Command: ./check_memory
// .....
// ==25448== LEAK SUMMARY:
// ==25448==    definitely lost: 8 bytes in 2 blocks
// ==25448==    indirectly lost: 0 bytes in 0 blocks
// ==25448==      possibly lost: 0 bytes in 0 blocks
// ==25448==    still reachable: 0 bytes in 0 blocks
// ==25448==         suppressed: 0 bytes in 0 blocks
// ==25448== 
// ==25448== ERROR SUMMARY: 8 errors from 8 contexts (suppressed: 0 from 0)

#include <iostream>

int main()
{
    int *ptr = new int(5);
    int a;

    // 内存越界读
    std::cout << ptr[6] << std::endl;

    // 内存越界写
    ptr[6] = 1;

    // 使用已经释放的内存
    std::cout << *ptr << std::endl;

    // 使用未初始化的变量
    std::cout << a << std::endl;

    // 内存泄漏
    ptr = new int(5);

    return 0;
}
