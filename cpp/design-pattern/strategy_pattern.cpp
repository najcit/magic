// strategy_pattern.cpp

// 运行程序
// g++ strategy_pattern.cpp -o strategy_pattern && ./strategy_pattern

// 结果输出
// Executing strategy A.
// Executing strategy B.

#include <iostream>

class Strategy
{
public:
    virtual void execute() = 0;
};

class ConcreteStrategyA : public Strategy
{
public:
    void execute() override
    {
        std::cout << "Executing strategy A." << std::endl;
    }
};

class ConcreteStrategyB : public Strategy
{
public:
    void execute() override
    {
        std::cout << "Executing strategy B." << std::endl;
    }
};

class Context
{
private:
    Strategy *strategy;

public:
    Context(Strategy *strategy) : strategy(strategy) {}

    void setStrategy(Strategy *strategy)
    {
        this->strategy = strategy;
    }

    void executeStrategy()
    {
        strategy->execute();
    }
};

int main(int argc, char *argv[])
{
    Strategy *strategyA = new ConcreteStrategyA();
    Strategy *strategyB = new ConcreteStrategyB();

    Context context(strategyA);

    context.executeStrategy();

    context.setStrategy(strategyB);

    context.executeStrategy();

    delete strategyA;
    delete strategyB;

    return 0;
}
