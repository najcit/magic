// flyweight_pattern.cpp

// 运行程序
// gcc flyweight_pattern.cpp -o flyweight_pattern && ./flyweight_pattern

#include <iostream>
#include <unordered_map>

// 抽象享元类
class Flyweight
{
public:
    virtual void operation(int extrinsicState) = 0;
};

// 具体享元类
class ConcreteFlyweight : public Flyweight
{
public:
    void operation(int extrinsicState) override
    {
        std::cout << "extrinsic state: " << extrinsicState << std::endl;
    }
};

// 享元工厂类
class FlyweightFactory
{
private:
    std::unordered_map<std::string, Flyweight *> flyweights;

public:
    Flyweight *getFlyweight(const std::string &key)
    {
        if (flyweights.find(key) == flyweights.end())
        {
            flyweights[key] = new ConcreteFlyweight();
        }
        return flyweights[key];
    }
};

int main(int argc, char *argv[])
{
    FlyweightFactory factory;
    Flyweight *flyweight1 = factory.getFlyweight("key1");
    flyweight1->operation(1);

    Flyweight *flyweight2 = factory.getFlyweight("key2");
    flyweight2->operation(2);

    Flyweight *flyweight3 = factory.getFlyweight("key1");
    flyweight3->operation(3);

    delete flyweight1;
    delete flyweight2;
    // delete flyweight3; flyweight1 和 flyweight3 是共享同一个对象，只需释放一次

    return 0;
}
