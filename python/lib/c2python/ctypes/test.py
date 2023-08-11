# test.py

# 运行测试脚本
# python test.py

from ctypes import CDLL
example = CDLL('./example.so')

print(example.add(1, 2))
