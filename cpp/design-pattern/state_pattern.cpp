// state_pattern.cpp

// 运行程序
// g++ state_pattern.cpp -o state_pattern && ./state_pattern

// 结果输出
// Handle in State A
// Handle in State B

#include <iostream>

class State
{
public:
    virtual void handle() = 0;
};

class ConcreteStateA : public State
{
public:
    void handle() override
    {
        std::cout << "Handle in State A" << std::endl;
    }
};

class ConcreteStateB : public State
{
public:
    void handle() override
    {
        std::cout << "Handle in State B" << std::endl;
    }
};

class Context
{
private:
    State *state;

public:
    Context(State *initialState) : state(initialState) {}

    void update(State *newState)
    {
        state = newState;
    }

    void request()
    {
        state->handle();
    }
};

int main(int argc, char *argv[])
{
    State *stateA = new ConcreteStateA();
    State *stateB = new ConcreteStateB();

    Context context(stateA);
    context.request();
    context.update(stateB);
    context.request();

    delete stateA;
    delete stateB;

    return 0;
}