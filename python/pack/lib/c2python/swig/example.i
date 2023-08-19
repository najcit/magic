// example.i

// 依据接口描述文件生成 example_wrap.c 和 example.py 文件
// swig -python example.i
// 根据 example_wrap.c 文件生成 _example*.so 共享库
// gcc -shared -fPIC `python3-config --includes` example_wrap.c -o _example`python3-config --extension-suffix`

%module example

%{
#include "example.c"
%}

%include "example.c"
