# CMake_Learn
学习来源：b站up主课程——[比飞鸟贵重的多_HKL](https://www.bilibili.com/video/BV1Mw411M761)

##### 最底层逻辑
一个厨师做菜，抛开味道不谈，他至少要知道需要什么原材料以及这些原材料都在哪？

##### CPP/C语言为什么会有头文件？
习惯写法：当存在多个CPP/C文件的时候，需要为每一个CPP/C文件都配一个头文件
1. 提升效率——程序运行时相关
2. 减少重复
3. 减轻依赖

#### 语法
- `cmak_mininum_required(VERSION X.XX)`：要求的cmake最小版本
- `project(project_name)`：设置项目的名称
- `add_subdirectory(xxxx)`: 添加子目录到build路径
- `add_executable(name xxx xxxx)`: 利用后面的xxx源文件，构建name的可执行文件
- `include_directories(path)`: 把依赖的头文件路径放进来，源文件就不需要添加额外路径

##### 静态库
- `add_library(static_name xxx)`: 把xxx源文件编译成库文件`sn.a`或者`sn.lib`
- 直接`link_libraires(path/xxx.a xxx.lib)`: 使用绝对路径+静态库
- 先`link_directories(path)`: 链接到指定路径
- 再`target_link_libraries(name .a)`: 根据上面路径找到`.a`库进行链接

##### 动态库
- `.dll.a`是导入库——链接阶段需要，`.dll`是动态链接库——运行阶段需要
- `add_libaray(shared_name SHARED xxx)`: 需要加上`SHARED`，编译得到`.dll`和`.dll.a` or `.dll.lib`文件
- ★使用的时候，链接静态库文件`.dll.a`/`.dll.lib`文件，生成的可执行文件`.exe`要和上面的动态库`.dll`放在一个目录下！
- 即`link_directories(path)`+`target_link_libraries(name .dll.a)`得到`name.exe`，再将`.lib`动态库文件放到同一目录
