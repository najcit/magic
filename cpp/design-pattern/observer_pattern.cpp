// observer_pattern.cpp

// 运行程序
// g++ observer_pattern.cpp -o observer_pattern && ./observer_pattern

// 结果输出
// ConcreteObserver1 received the update.
// ConcreteObserver2 received the update.
// ConcreteObserver2 received the update.

#include <iostream>
#include <vector>

class Observer
{
public:
    virtual void update() = 0;
};

class ConcreteObserver1 : public Observer
{
public:
    void update() override
    {
        std::cout << "ConcreteObserver1 received the update." << std::endl;
    }
};

class ConcreteObserver2 : public Observer
{
public:
    void update() override
    {
        std::cout << "ConcreteObserver2 received the update." << std::endl;
    }
};

class Subject
{
public:
    virtual void attach(Observer *observer) = 0;
    virtual void detach(Observer *observer) = 0;
    virtual void notify() = 0;
};

class ConcreteSubject : public Subject
{
private:
    std::vector<Observer *> observers;

public:
    void attach(Observer *observer) override
    {
        observers.push_back(observer);
    }

    void detach(Observer *observer) override
    {
        for (auto it = observers.begin(); it != observers.end(); ++it)
        {
            if (*it == observer)
            {
                observers.erase(it);
                break;
            }
        }
    }

    void notify() override
    {
        for (auto observer : observers)
        {
            observer->update();
        }
    }
};

int main(int argc, char *argv[])
{
    ConcreteSubject subject;
    ConcreteObserver1 observer1;
    ConcreteObserver2 observer2;

    subject.attach(&observer1);
    subject.attach(&observer2);

    subject.notify();

    subject.detach(&observer1);

    subject.notify();

    return 0;
}
