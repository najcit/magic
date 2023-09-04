// interpreter_pattern.cpp

// 运行程序
// g++ interpreter_pattern.cpp -o interpreter_pattern && ./interpreter_pattern

// 输出结果
// Result: true

#include <iostream>
#include <unordered_map>

class Context
{
public:
    void setVariable(const std::string &name, bool value)
    {
        variables[name] = value;
    }

    bool getVariable(const std::string &name)
    {
        return variables[name];
    }

private:
    std::unordered_map<std::string, bool> variables;
};

class Expression
{
public:
    virtual ~Expression() {}
    virtual bool interpret(Context &context) = 0;
};

class TerminalExpression : public Expression
{
public:
    TerminalExpression(const std::string &variable) : variable(variable) {}

    bool interpret(Context &context) override
    {
        return context.getVariable(variable);
    }

private:
    std::string variable;
};

class AndExpression : public Expression
{
public:
    AndExpression(Expression *left, Expression *right) : left(left), right(right) {}

    ~AndExpression()
    {
        delete left;
        left = nullptr;
        delete right;
        right = nullptr;
    }

    bool interpret(Context &context) override
    {
        return left->interpret(context) && right->interpret(context);
    }

private:
    Expression *left;
    Expression *right;
};

class OrExpression : public Expression
{
public:
    OrExpression(Expression *left, Expression *right) : left(left), right(right) {}

    ~OrExpression()
    {
        delete left;
        left = nullptr;
        delete right;
        right = nullptr;
    }

    bool interpret(Context &context) override
    {

        return left->interpret(context) || right->interpret(context);
    }

private:
    Expression *left;
    Expression *right;
};

int main(int argc, char *argv[])
{
    Context context;
    context.setVariable("A", true);
    context.setVariable("B", false);
    context.setVariable("C", true);
    Expression *expression = new OrExpression(
        new AndExpression(new TerminalExpression("A"), new TerminalExpression("B")),
        new TerminalExpression("C"));
    bool result = expression->interpret(context);
    std::cout << "Result: " << std::boolalpha << result << std::endl;
    delete expression;
    expression = nullptr;

    return 0;
}
