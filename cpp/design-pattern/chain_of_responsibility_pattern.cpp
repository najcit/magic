// chain_of_responsibility_pattern.cpp

// 运行程序
// g++ chain_of_responsibility_pattern.cpp -o chain_of_responsibility_pattern && ./chain_of_responsibility_pattern

// 输出结果
// ConcreteHandlerA handles the request: 5
// ConcreteHandlerB handles the request: 15
// ConcreteHandlerC handles the request: 25

#include <iostream>

class Handler
{
public:
    Handler() : next(nullptr) {}
    virtual ~Handler() {}

    void setNext(Handler *handler)
    {
        next = handler;
    }

    virtual void handleRequest(int request) = 0;

protected:
    Handler *next;
};

class ConcreteHandlerA : public Handler
{
public:
    void handleRequest(int request) override
    {
        if (request >= 0 && request < 10)
        {
            std::cout << "ConcreteHandlerA handles the request: " << request << std::endl;
        }
        else if (next != nullptr)
        {
            next->handleRequest(request);
        }
    }
};

class ConcreteHandlerB : public Handler
{
public:
    void handleRequest(int request) override
    {
        if (request >= 10 && request < 20)
        {
            std::cout << "ConcreteHandlerB handles the request: " << request << std::endl;
        }
        else if (next != nullptr)
        {
            next->handleRequest(request);
        }
    }
};

// 具体处理者C
class ConcreteHandlerC : public Handler
{
public:
    void handleRequest(int request) override
    {
        if (request >= 20 && request < 30)
        {
            std::cout << "ConcreteHandlerC handles the request: " << request << std::endl;
        }
        else if (next != nullptr)
        {
            next->handleRequest(request);
        }
    }
};

int main(int argc, char *argv[])
{
    Handler *handlerA = new ConcreteHandlerA();
    Handler *handlerB = new ConcreteHandlerB();
    Handler *handlerC = new ConcreteHandlerC();
    handlerA->setNext(handlerB);
    handlerB->setNext(handlerC);

    handlerA->handleRequest(5);
    handlerA->handleRequest(15);
    handlerA->handleRequest(25);

    delete handlerA;
    delete handlerB;
    delete handlerC;

    return 0;
}
