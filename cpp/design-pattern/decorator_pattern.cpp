// decorator_pattern.cpp

// 运行程序
// g++ decorator_pattern.cpp -o decorator_pattern && ./decorator_pattern

// 结果输出
// Coffee with milk: 12
// Coffee with sugar: 11

#include <iostream>

class Beverage
{
public:
    virtual double cost() = 0;
};

class Coffee : public Beverage
{
public:
    double cost() override
    {
        return 10.0;
    }
};

class CondimentDecorator : public Beverage
{
protected:
    Beverage *beverage;

public:
    CondimentDecorator(Beverage *beverage)
    {
        this->beverage = beverage;
    }

    double cost() override
    {
        return beverage->cost();
    }
};

class Milk : public CondimentDecorator
{
public:
    Milk(Beverage *beverage) : CondimentDecorator(beverage) {}

    double cost() override
    {
        return beverage->cost() + 2.0;
    }
};

class Sugar : public CondimentDecorator
{
public:
    Sugar(Beverage *beverage) : CondimentDecorator(beverage) {}

    double cost() override
    {
        return beverage->cost() + 1.0;
    }
};

int main(int argc, char *argv[])
{
    Beverage *coffee = new Coffee();
    Beverage *coffee_with_milk = new Milk(coffee);
    Beverage *coffee_with_sugar = new Sugar(coffee);

    std::cout << "Coffee with milk: " << coffee_with_milk->cost() << std::endl;   // 输出 12.0
    std::cout << "Coffee with sugar: " << coffee_with_sugar->cost() << std::endl; // 输出 11.0

    delete coffee;
    delete coffee_with_milk;
    delete coffee_with_sugar;

    return 0;
}
