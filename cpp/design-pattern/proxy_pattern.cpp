// proxy_pattern.cpp

// 运行程序
// g++ proxy_pattern.cpp -o proxy_pattern && ./proxy_pattern

// 结果输出
// Proxy: Logging before request.
// RealSubject: Handling request.
// Proxy: Logging after request.

#include <iostream>

class Subject
{
public:
    virtual void request() = 0;
};

class RealSubject : public Subject
{
public:
    void request() override
    {
        std::cout << "RealSubject: Handling request." << std::endl;
    }
};

class Proxy : public Subject
{
private:
    RealSubject *realSubject;

public:
    Proxy()
    {
        realSubject = new RealSubject();
    }

    ~Proxy()
    {
        delete realSubject;
    }

    void request() override
    {
        std::cout << "Proxy: Logging before request." << std::endl;
        realSubject->request();
        std::cout << "Proxy: Logging after request." << std::endl;
    }
};

int main(int argc, char *argv[])
{
    Proxy proxy;
    proxy.request();
    return 0;
}
