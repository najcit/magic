// exmpale.cpp

// 编译生成动态链接库
// g++ -std=c++11 -shared -fPIC `python -m pybind11 --includes` example.cpp -o example`python3-config --extension-suffix`

#include <pybind11/pybind11.h>

namespace example
{
    int add(int i, int j)
    {
        return i + j;
    }
}

int sub(int i, int j)
{
    return i - j;
}

PYBIND11_MODULE(example, m)
{
    m.doc() = "pybind11 example plugin";
    m.def("add", &example::add, "A function that two numbers adds ");
    m.def("sub", &sub, "A function that two numbers sub");
}