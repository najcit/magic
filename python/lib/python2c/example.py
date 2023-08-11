# example.py

# 编译生成动态链接库
# cythonize example.py -i

def fib(n):
    """Print the Fibonacci series up to n."""
    a, b = 0, 1
    while b < n:
        print(b, end=' ')
        a, b = b, a + b