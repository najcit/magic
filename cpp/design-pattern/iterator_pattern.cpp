// iterator_pattern.cpp

// 运行程序
// g++ iterator_pattern.cpp -o iterator_pattern && ./iterator_pattern

// 结果输出
// 1
// 2
// 3
// 4
// 5

#include <iostream>
#include <vector>

template <typename T>
class Iterator
{
public:
    virtual bool hasNext() = 0;
    virtual T next() = 0;
};

template <typename T>
class MyIterator : public Iterator<T>
{
private:
    std::vector<T> data;
    size_t index;

public:
    MyIterator(const std::vector<T> &data) : data(data), index(0) {}

    bool hasNext() override
    {
        return index < data.size();
    }

    T next() override
    {
        if (hasNext())
        {
            return data[index++];
        }
        throw std::out_of_range("No more elements.");
    }
};

template <typename T>
class MyContainer
{
private:
    std::vector<T> data;

public:
    void add(const T &item)
    {
        data.push_back(item);
    }

    Iterator<T> *createIterator()
    {
        return new MyIterator<T>(data);
    }
};

int main(int argc, char *argv[])
{
    MyContainer<int> container;
    container.add(1);
    container.add(2);
    container.add(3);
    container.add(4);
    container.add(5);

    Iterator<int> *iterator = container.createIterator();
    while (iterator->hasNext())
    {
        std::cout << iterator->next() << std::endl;
    }

    delete iterator;

    return 0;
}
