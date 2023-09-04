// mediator_pattern.cpp

// 运行程序
// g++ mediator_pattern.cpp -o mediator_pattern && ./mediator_pattern

// 输出结果
// colleague2 Received message from colleague1 : Hello, everyone!
// colleague3 Received message from colleague1 : Hello, everyone!
// colleague1 Received message from colleague2 : Hello, everyone!
// colleague3 Received message from colleague2 : Hello, everyone!
// colleague1 Received message from colleague3 : Hello, everyone!
// colleague2 Received message from colleague3 : Hello, everyone!

#include <iostream>
#include <string>
#include <vector>

class Colleague;

class Mediator
{
public:
    virtual void sendMessage(const std::string &message, Colleague *colleague) = 0;
};

class Colleague
{
protected:
    Mediator *mediator;

public:
    explicit Colleague(std::string name, Mediator *mediator) : name(name), mediator(mediator) {}

    virtual void sendMessage(const std::string &message) = 0;

    virtual void receiveMessage(const std::string &message, Colleague *sender) = 0;

    std::string name;
};

class ConcreteMediator : public Mediator
{
private:
    std::vector<Colleague *> colleagues;

public:
    void addColleague(Colleague *colleague)
    {
        colleagues.push_back(colleague);
    }

    void sendMessage(const std::string &message, Colleague *sender) override
    {
        for (auto colleague : colleagues)
        {
            if (colleague != sender)
            {
                colleague->receiveMessage(message, sender);
            }
        }
    }
};

class ConcreteColleague : public Colleague
{
public:
    explicit ConcreteColleague(std::string name, Mediator *mediator) : Colleague(name, mediator) {}

    void sendMessage(const std::string &message) override
    {
        mediator->sendMessage(message, this);
    }

    void receiveMessage(const std::string &message, Colleague *sender) override
    {
        std::cout << this->name << " Received message from " << sender->name << " : " << message << std::endl;
    }
};

int main(int argc, char *argv[])
{
    ConcreteMediator mediator;
    ConcreteColleague colleague1("colleague1", &mediator);
    ConcreteColleague colleague2("colleague2", &mediator);
    ConcreteColleague colleague3("colleague3", &mediator);

    mediator.addColleague(&colleague1);
    mediator.addColleague(&colleague2);
    mediator.addColleague(&colleague3);
    colleague1.sendMessage("Hello, everyone!");
    colleague2.sendMessage("Hello, everyone!");
    colleague3.sendMessage("Hello, everyone!");

    return 0;
}
