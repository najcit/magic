// visitor_pattern.cpp

// 运行程序
// g++ visitor_pattern.cpp -o visitor_pattern && ./visitor_pattern

// 输出结果
// ConcreteElementA operationA
// ConcreteElementB operationB

#include <iostream>
#include <vector>

class Element;

class Visitor
{
public:
    virtual void visit(Element *element) = 0;
};

class Element
{
public:
    virtual void accept(Visitor *visitor) = 0;
};

class ConcreteElementA : public Element
{
public:
    void accept(Visitor *visitor) override
    {
        visitor->visit(this);
    }

    void operationA()
    {
        std::cout << "ConcreteElementA operationA" << std::endl;
    }
};

class ConcreteElementB : public Element
{
public:
    void accept(Visitor *visitor) override
    {
        visitor->visit(this);
    }

    void operationB()
    {
        std::cout << "ConcreteElementB operationB" << std::endl;
    }
};

class ConcreteVisitor : public Visitor
{
public:
    void visit(Element *element) override
    {
        if (dynamic_cast<ConcreteElementA *>(element))
        {
            ConcreteElementA *elementA = dynamic_cast<ConcreteElementA *>(element);
            elementA->operationA();
        }
        else if (dynamic_cast<ConcreteElementB *>(element))
        {
            ConcreteElementB *elementB = dynamic_cast<ConcreteElementB *>(element);
            elementB->operationB();
        }
    }
};

int main(int argc, char *argv[])
{
    std::vector<Element *> elements;
    elements.push_back(new ConcreteElementA());
    elements.push_back(new ConcreteElementB());

    ConcreteVisitor visitor;
    for (Element *element : elements)
    {
        element->accept(&visitor);
    }

    for (Element *element : elements)
    {
        delete element;
    }

    return 0;
}