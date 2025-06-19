# CMake_Learn
学习来源：b站up主课程——[比飞鸟贵重的多_HKL](https://www.bilibili.com/video/BV1Mw411M761)

##### 最底层逻辑
一个厨师做菜，抛开味道不谈，他至少要知道需要什么原材料以及这些原材料都在哪？

##### CPP/C语言为什么会有头文件？
习惯写法：当存在多个CPP/C文件的时候，需要为每一个CPP/C文件都配一个头文件
1. 提升效率——程序运行时相关
2. 减少重复
3. 减轻依赖
---
#### 语法
- `cmak_mininum_required(VERSION X.XX)`：要求的cmake最小版本
- `project(project_name)`：设置项目的名称
- `add_subdirectory(xxxx)`: 添加子目录到build路径
- `add_executable(name xxx xxxx)`: 利用后面的xxx源文件，构建name的可执行文件
- `include_directories(path)`: 把依赖的头文件路径放进来，源文件就不需要添加额外路径
- `find_package(lib REQUIRES)`: 自动查找外部库lib，并生成相关变量
- `aux_source_directory(path Var)`：递归收集path目录下所有的`.cpp`文件，保存到`Var`变量
- `enable_testing()`：启动CTest测试框架

##### 静态库
- `add_library(static_name xxx)`: 把xxx源文件编译成库文件`sn.a`或者`sn.lib`
- 直接`link_libraires(path/xxx.a xxx.lib)`: 使用绝对路径+静态库,指定库
- 先`link_directories(path)`: 链接到指定路径
- 再`target_link_libraries(name .a)`: 根据上面路径找到`.a`库进行链接

##### 动态库
- `.dll.a`是导入库——链接阶段需要，`.dll`/`.so`是动态链接库——运行阶段需要
- `add_libaray(shared_name SHARED xxx)`: 需要加上`SHARED`，编译得到`.dll`和`.dll.a` or `.dll.lib`文件
- ★使用的时候，链接静态库文件`.dll.a`/`.dll.lib`文件，生成的可执行文件`.exe`要和上面的动态库`.dll`放在一个目录下！
- 即`link_directories(path)`+`target_link_libraries(name .dll.a)`得到`name.exe`，再将`.lib`动态库文件放到同一目录
- Windows平台（DLL加载顺序）：应用程序所在目录→系统目录→Windows目录→当前工作目录→PATH环境变量
- Linux平台（SO加载顺序）：LD_PRELOAD环境变量指定的库→DT_RPATH等等
- 记住两者不一样即可~
---
### 四个阶段

1. **预处理阶段**
    
    **作用**：处理 `#include`、`#define`、条件编译等指令，生成纯净的C++代码供后续编译
    
    ```bash
    // -E: 让 g++ 只执行预处理（Preprocessing），生成预处理后的输出
    // .i: 预处理后的源代码文件（展开宏、包含头文件、删除注释等）
    g++ -E main.cpp -o main.i
    ```
    
    1. 处理`#include` 指令
        - 将头文件（`.h`、`.hpp`）的内容直接插入到当前文件中
    2. 处理宏定义`#define` 和宏展开
    3. 条件编译（`#ifdef` ,`#ifndef` ,`#else` ,`#endif` )
    4. 删除注释
    5. 处理`#pragma` 指令
        - 编译器特定的指令（如 `#pragma once` 用于防止头文件重复包含）
    6. 处理其他预处理指令
2. **编译**
    
    **作用**：将预处理后的C++代码（`main.i`）转换为目标平台的汇编代码
    
    ```bash
    // -S: 让 g++ 只编译（Compilation），生成汇编代码（不汇编或链接）
    // .s: 汇编代码文件（人类可读的低级指令，与CPU架构相关）
    g++ -S main.i -o main.s
    ```
    
3. **汇编**
    
    **作用**：将汇编代码（`main.s`）转换为二进制机器指令（`.o` 文件）
    
    ```bash
    // -C: 让 g++ 执行汇编（Assembly），将汇编代码转换为机器码（目标文件）
    // .o: 目标文件（Object File），包含机器码和符号表，但未链接
    g++ -C main.s -o main.o
    ```
    
4. **链接**
    
    **作用**：合并多个目标文件（如 `main.o` 和 `add.o`），解析外部依赖（如库函数），生成可执行程序
    
    ```bash
    // Linux/Mac: 可执行文件无需后缀
    // Windows: 依赖.exe后缀表示可执行文件
    g++ main.o add.o -o main
    ```
    
5. 一步到位
    
    ```bash
    g++ main.cpp add.cpp -o main
    ```
    
---
### Makefile

- 以文件的形式，把指令集成在一起，便于管理和扩展等
- **注意**：这个是只能在Linux系统上可以这么做
- 步骤：编写`Makefile` 文件，再在终端执行`make` 指令
- 一步到位
    
    ```makefile
    main: main.cpp add.cpp
    		g++ main.cpp add.cpp -o main
    ```
    
- 生成中间结果
    
    ```makefile
    main: main.o add.o
    		g++ main.o add.o -o main
    main.o add.o: main.s add.s
    		g++ -c main.s -o main.o
    		g++ -c add.s -o add.o
    main.s add.s: main.i add.i
    		g++ -S main.i -o main.s
    		g++ -S add.i -o add.s
    main.i add.i: main.cpp add.cpp
    		g++ -E main.cpp -o main.i
    		g++ -E add.cpp -o add.i
    ```
    
### CMake

- 大一统！Linux和Windows系统都支持
- 跨平台！！！！
- 可视化cmake的过程（根据已经写好的CMakeLists.txt文件）
    
    ```bash
    mkdir build && cd build
    cmake .. -DCMAKE_VERBOSE_MAKEFILE=ON
    cmake --build .
    ```
---
### Modern CMake
- 模块化
  
| **指令** | **作用** | **常用参数（作用域）** |
| --- | --- | --- |
| **`add_library`** | 将源代码编译为静态库/动态库 | 无 |
| **`target_include_directories`** | 指定头文件搜索路径，控制路径的可见性 | `PUBLIC`、`PRIVATE`、`INTERFACE` |
| **`target_link_libraries`** | 声明库或可执行文件的依赖关系，自动传递链接和编译依赖 | `PUBLIC`、`PRIVATE`、`INTERFACE` |
  