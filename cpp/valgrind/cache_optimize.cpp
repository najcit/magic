// cache_optimize.cpp

// 编译程序
// g++ cache_optimize.cpp -o cache_optimize -g

// 运行程序
// valgrind --tool=cachegrind ./cache_optimize

// 程序输出
// --------------------------------------------------------------------------------
// I1 cache:         32768 B, 64 B, 8-way associative
// D1 cache:         49152 B, 64 B, 12-way associative
// LL cache:         12582912 B, 64 B, 12-way associative
// Command:          ./cache_optimize
// Data file:        cachegrind.out.35767
// Events recorded:  Ir I1mr ILmr Dr D1mr DLmr Dw D1mw DLmw
// Events shown:     Ir I1mr ILmr Dr D1mr DLmr Dw D1mw DLmw
// Event sort order: Ir I1mr ILmr Dr D1mr DLmr Dw D1mw DLmw
// Thresholds:       0.1 100 100 100 100 100 100 100 100
// Include dirs:     
// User annotated:   
// Auto-annotation:  on
// ......

#include <iostream>

const int SIZE = 1000;
int array[SIZE];

int main() {
    for (int i = 0; i < SIZE; i++) {
        array[i] = i;
    }

    int sum = 0;
    for (int i = 0; i < SIZE; i++) {
        sum += array[i];
    }

    std::cout << "Sum: " << sum << std::endl;

    return 0;
}
