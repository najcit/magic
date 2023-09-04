// singleton_pattern.cpp

// 运行程序
// g++ singleton_pattern.cpp -o singleton_pattern && ./singleton_pattern

// 输出结果
// Hello, I am a singleton object: 0x555555558152
// Hello, I am a singleton object: 0x555555558152

#include <iostream>
#include <thread>

class Singleton
{
public:
    static Singleton &getInstance()
    {
        static Singleton instance;
        return instance;
    }

    void showMessage()
    {
        std::cout << "Hello, I am a singleton object: " << this << std::endl;
    }

    // 禁止拷贝构造函数和赋值运算符
    Singleton(const Singleton &) = delete;
    Singleton &operator=(const Singleton &) = delete;

private:
    // 私有构造函数，防止外部创建实例
    Singleton() {}
};

int main(int argc, char *argv[])
{
    Singleton &instance = Singleton::getInstance();
    instance.showMessage();

    std::thread my_thread = std::thread([](){
        Singleton &instance = Singleton::getInstance();
        instance.showMessage();
    });
    my_thread.join();

    return 0;
}
