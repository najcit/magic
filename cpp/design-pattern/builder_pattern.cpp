// builder_pattern.cpp

// 运行程序
// g++ builder_pattern.cpp -o builder_pattern && ./builder_pattern

// 结果输出
// Part 1: Part 1, Part 2: Part 2, Part 3: Part 3
// Part 1: New Part 1, Part 2: New Part 2, Part 3: New Part 3

#include <iostream>
#include <string>

class Product
{
public:
    void setPart1(const std::string &part1)
    {
        part1_ = part1;
    }

    void setPart2(const std::string &part2)
    {
        part2_ = part2;
    }

    void setPart3(const std::string &part3)
    {
        part3_ = part3;
    }

    std::string toString() const
    {
        return "Part 1: " + part1_ + ", Part 2: " + part2_ + ", Part 3: " + part3_;
    }

private:
    std::string part1_;
    std::string part2_;
    std::string part3_;
};

class Builder
{
public:
    virtual void buildPart1() = 0;
    virtual void buildPart2() = 0;
    virtual void buildPart3() = 0;
    virtual Product getProduct() = 0;
};

class ConcreteBuilder : public Builder
{
public:
    void buildPart1() override
    {
        product_.setPart1("Part 1");
    }

    void buildPart2() override
    {
        product_.setPart2("Part 2");
    }

    void buildPart3() override
    {
        product_.setPart3("Part 3");
    }

    Product getProduct() override
    {
        return product_;
    }

private:
    Product product_;
};

class NewConcreteBuilder : public Builder
{
public:
    void buildPart1() override
    {
        product_.setPart1("New Part 1");
    }

    void buildPart2() override
    {
        product_.setPart2("New Part 2");
    }

    void buildPart3() override
    {
        product_.setPart3("New Part 3");
    }

    Product getProduct() override
    {
        return product_;
    }

private:
    Product product_;
};

class Director
{
public:
    void setBuilder(Builder *builder)
    {
        builder_ = builder;
    }

    void construct()
    {
        builder_->buildPart1();
        builder_->buildPart2();
        builder_->buildPart3();
    }

private:
    Builder *builder_;
};

int main()
{
    Director director;

    ConcreteBuilder builder;
    director.setBuilder(&builder);
    director.construct();
    Product product = builder.getProduct();
    std::cout << product.toString() << std::endl;

    NewConcreteBuilder newBuilder;
    director.setBuilder(&newBuilder);
    director.construct();
    Product newProduct = newBuilder.getProduct();
    std::cout << newProduct.toString() << std::endl;

    return 0;
}
