// bridge_pattern.cpp

// 运行脚本
// g++ bridge_pattern.cpp -o bridge_pattern && ./bridge_pattern

// 输出结果
// Concrete Abstraction operation
// Concrete Implementor operation

#include <iostream>

// 实现部分的接口
class Implementor
{
public:
    virtual void operationImpl() = 0;
};

// 具体实现类A
class ConcreteImplementor : public Implementor
{
public:
    void operationImpl() override
    {
        std::cout << "Concrete Implementor operation" << std::endl;
    }
};

class Abstraction
{
protected:
    Implementor *implementor;

public:
    Abstraction(Implementor *impl) : implementor(impl) {}

    virtual void operation() = 0;
};

class ConcreteAbstraction : public Abstraction
{
public:
    ConcreteAbstraction(Implementor *impl) : Abstraction(impl) {}

    void operation() override
    {
        std::cout << "Concrete Abstraction operation" << std::endl;
        implementor->operationImpl();
    }
};


int main(int argc, char *argv[])
{
    Implementor *implementor = new ConcreteImplementor();
    Abstraction *abstraction = new ConcreteAbstraction(implementor);
    abstraction->operation();

    delete implementor;
    delete abstraction;

    return 0;
}
