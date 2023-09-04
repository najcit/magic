// perf_profile.cpp

// 编译程序
// g++ perf_profile.cpp -o perf_profile -g

// 运行程序
//  valgrind --tool=callgrind ./perf_profile
//  valgrind callgrind_annotate callgrind.out.*

// 程序输出
// ......
// --------------------------------------------------------------------------------
// Ir
// --------------------------------------------------------------------------------
// 175,705,384 (100.0%)  PROGRAM TOTALS
// --------------------------------------------------------------------------------
// Ir                   file:function
// --------------------------------------------------------------------------------
// ....

#include <iostream>
#include <vector>

int main()
{
    std::vector<int> numbers;
    for (int i = 0; i < 1000000; i++)
    {
        numbers.push_back(i);
    }

    int sum = 0;
    for (int num : numbers)
    {
        sum += num;
    }

    std::cout << "Sum: " << sum << std::endl;

    return 0;
}
