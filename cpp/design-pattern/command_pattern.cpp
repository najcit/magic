// command_pattern.cpp

// 运行程序
// g++ command_pattern.cpp -o command_pattern && ./command_pattern

// 输出结果
// Receiver: Action A
// Receiver: Action B

#include <iostream>
#include <vector>

class Receiver
{
public:
    void actionA()
    {
        std::cout << "Receiver: Action A" << std::endl;
    }

    void actionB()
    {
        std::cout << "Receiver: Action B" << std::endl;
    }
};

class Command
{
public:
    virtual void execute() = 0;
};

class ConcreteCommandA : public Command
{
private:
    Receiver *receiver;

public:
    ConcreteCommandA(Receiver *rec) : receiver(rec) {}

    void execute() override
    {
        receiver->actionA();
    }
};

class ConcreteCommandB : public Command
{
private:
    Receiver *receiver;

public:
    ConcreteCommandB(Receiver *rec) : receiver(rec) {}

    void execute() override
    {
        receiver->actionB();
    }
};

class Invoker
{
private:
    Command *command;

public:
    void setCommand(Command *cmd)
    {
        command = cmd;
    }

    void executeCommand()
    {
        command->execute();
    }
};

int main(int argc, char *argv[])
{
    Receiver *receiver = new Receiver();
    Command *commandA = new ConcreteCommandA(receiver);
    Command *commandB = new ConcreteCommandB(receiver);

    Invoker invoker;
    invoker.setCommand(commandA);
    invoker.executeCommand();
    invoker.setCommand(commandB);
    invoker.executeCommand();

    delete receiver;
    delete commandA;
    delete commandB;

    return 0;
}
