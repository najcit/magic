// memento_pattern.cpp

// 运行程序
// g++ iterator_pattern.cpp -o iterator_pattern && ./iterator_pattern

// 输出结果
// Current State: State 4
// Current State: State 3
// Current State: State 2

#include <iostream>
#include <string>
#include <vector>

class Memento
{
public:
    Memento(const std::string &state) : state_(state) {}

    std::string GetState() const
    {
        return state_;
    }

private:
    std::string state_;
};

class Originator
{
public:
    void SetState(const std::string &state)
    {
        state_ = state;
    }

    std::string GetState() const
    {
        return state_;
    }

    Memento *CreateMemento()
    {
        return new Memento(state_);
    }

    void RestoreMemento(Memento *memento)
    {
        state_ = memento->GetState();
        delete memento;
        memento = nullptr;
    }

private:
    std::string state_;
};

class Caretaker
{
public:
    void SaveMemeto(Memento *memento)
    {
        mementos_.push_back(memento);
    }

    Memento *LastMemento()
    {
        Memento *memento = mementos_.back();
        mementos_.pop_back();
        return memento;
    }

private:
    std::vector<Memento *> mementos_;
};

int main(int argc, char *argv[])
{
    Originator originator;
    Caretaker caretaker;
    originator.SetState("State 1");
    caretaker.SaveMemeto(originator.CreateMemento());
    originator.SetState("State 2");
    caretaker.SaveMemeto(originator.CreateMemento());
    originator.SetState("State 3");
    caretaker.SaveMemeto(originator.CreateMemento());
    originator.SetState("State 4");
    std::cout << "Current State: " << originator.GetState() << std::endl;
    originator.RestoreMemento(caretaker.LastMemento());
    std::cout << "Current State: " << originator.GetState() << std::endl;
    originator.RestoreMemento(caretaker.LastMemento());
    std::cout << "Current State: " << originator.GetState() << std::endl;

    return 0;
}
