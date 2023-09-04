// composite_pattern.cpp

// 运行程序
// g++ composite_pattern.cpp -o composite_pattern && ./composite_pattern

// 结果输出
// Composite operation
// Leaf operation
// Leaf operation

#include <iostream>
#include <vector>
#include <algorithm>

class Component
{
public:
    virtual void operation() = 0;
};

class Leaf : public Component
{
public:
    void operation() override
    {
        std::cout << "Leaf operation" << std::endl;
    }
};

class Composite : public Component
{
private:
    std::vector<Component *> components;

public:
    void add(Component *component)
    {
        components.push_back(component);
    }

    void remove(Component *component)
    {
        components.erase(std::remove(components.begin(), components.end(), component), components.end());
    }

    void operation() override
    {
        std::cout << "Composite operation" << std::endl;
        for (Component *component : components)
        {
            component->operation();
        }
    }
};

int main(int argc, char* argv[])
{
    Leaf leaf1;
    Leaf leaf2;
    Composite composite;

    composite.add(&leaf1);
    composite.add(&leaf2);
    composite.operation();

    return 0;
}
