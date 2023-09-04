// template_pattern.cpp

// 运行程序
// g++ template_pattern.cpp -o template_pattern && ./template_pattern

// 结果输出
// ConcreteClassA: Step 1
// ConcreteClassA: Step 2
// ConcreteClassA: Step 3
// ConcreteClassB: Step 1
// ConcreteClassB: Step 2
// ConcreteClassB: Step 3

#include <iostream>

class AbstractClass
{
public:
    void templateMethod()
    {

        step1();

        step2();

        step3();
    }

    virtual void step1() = 0;

    virtual void step2() = 0;

    virtual void step3() = 0;
};

class ConcreteClassA : public AbstractClass
{
public:
    void step1() override
    {

        std::cout << "ConcreteClassA: Step 1" << std::endl;
    }

    void step2() override
    {

        std::cout << "ConcreteClassA: Step 2" << std::endl;
    }

    void step3() override
    {

        std::cout << "ConcreteClassA: Step 3" << std::endl;
    }
};

class ConcreteClassB : public AbstractClass
{
public:
    void step1() override
    {

        std::cout << "ConcreteClassB: Step 1" << std::endl;
    }

    void step2() override
    {

        std::cout << "ConcreteClassB: Step 2" << std::endl;
    }

    void step3() override
    {

        std::cout << "ConcreteClassB: Step 3" << std::endl;
    }
};

int main(int argc, char *argv[])
{
    AbstractClass *classA = new ConcreteClassA();
    classA->templateMethod();

    AbstractClass *classB = new ConcreteClassB();
    classB->templateMethod();

    delete classA;
    delete classB;

    return 0;
}
