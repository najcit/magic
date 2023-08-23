// facade_pattern.cpp

// 运行程序
// gcc facade_pattern.cpp -o facade_pattern && ./facade_pattern

// 输出结果
// SubsystemA operation
// SubsystemB operation

#include <iostream>

class SubsystemA
{
public:
    void operationA()
    {
        std::cout << "SubsystemA operation" << std::endl;
    }
};

class SubsystemB
{
public:
    void operationB()
    {
        std::cout << "SubsystemB operation" << std::endl;
    }
};

class Facade
{
private:
    SubsystemA subsystemA;
    SubsystemB subsystemB;

public:
    void operationA()
    {
        subsystemA.operationA();
    }
    void operationB()
    {
        subsystemB.operationB();
    }
};

int main(int argc, char *argv[])
{
    Facade facade;
    facade.operationA();
    facade.operationB();

    return 0;
}
