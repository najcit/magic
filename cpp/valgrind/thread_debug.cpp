// thread_debug.cpp

// 编译程序
// g++ thread_debug.cpp -o thread_debug -g

// 运行程序
// valgrind -tool=helgrind --history-level=approx -s ./thread_debug

// 程序输出
// ==35418== ----------------------------------------------------------------
// ==35418== 
// ==35418== Possible data race during write of size 4 at 0x10C158 by thread #3
// ==35418== Locks held: none
// ==35418==    at 0x1092DA: incrementCounter() (thread_debug.cpp:9)
// ==35418==    by 0x109C06: void std::__invoke_impl<void, void (*)()>(std::__invoke_other, void (*&&)()) (invoke.h:61)
// ==35418==    by 0x109BB2: std::__invoke_result<void (*)()>::type std::__invoke<void (*)()>(void (*&&)()) (invoke.h:96)
// ==35418==    by 0x109B53: void std::thread::_Invoker<std::tuple<void (*)()> >::_M_invoke<0ul>(std::_Index_tuple<0ul>) (std_thread.h:259)
// ==35418==    by 0x109B23: std::thread::_Invoker<std::tuple<void (*)()> >::operator()() (std_thread.h:266)
// ==35418==    by 0x109B03: std::thread::_State_impl<std::thread::_Invoker<std::tuple<void (*)()> > >::_M_run() (std_thread.h:211)
// ==35418==    by 0x4947252: ??? (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.30)
// ==35418==    by 0x485396A: ??? (in /usr/libexec/valgrind/vgpreload_helgrind-amd64-linux.so)
// ==35418==    by 0x4B4BB42: start_thread (pthread_create.c:442)
// ==35418==    by 0x4BDCBB3: clone (clone.S:100)

#include <iostream>
#include <thread>
#include <mutex>

static int counter = 0;
// 线程不安全函数
void incrementCounter()
{
    counter++;
}

int main()
{
    std::thread t1(incrementCounter);
    std::thread t2(incrementCounter);

    t1.join();
    t2.join();

    std::cout << "Counter: " << counter << std::endl;

    return 0;
}
