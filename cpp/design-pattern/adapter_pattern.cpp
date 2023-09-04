// adapter_pattern.cpp

// 运行程序
// g++ adapter_pattern.cpp -o adapter_pattern && ./adapter_pattern

// 输出结果
// Adapter's request
// Adaptee's specific request

#include <iostream>

class Target
{
public:
    virtual void request() = 0;
};

class Adaptee
{
public:
    void specificRequest()
    {
        std::cout << "Adaptee's specific request" << std::endl;
    }
};

class Adapter : public Target
{
private:
    Adaptee *adaptee;

public:
    Adapter(Adaptee *adaptee) : adaptee(adaptee) {}

    void request() override
    {
        std::cout << "Adapter's request" << std::endl;
        adaptee->specificRequest();
    }
};

int main(int argc, char *argv[])
{
    Adaptee *adaptee = new Adaptee();
    Target *adapter = new Adapter(adaptee);

    adapter->request();

    delete adapter;
    delete adaptee;

    return 0;
}
