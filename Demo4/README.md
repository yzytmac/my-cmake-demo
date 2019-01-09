# 多目录多文件
把子目录编译成静态库的形式更适用于大型工程  
1. 子目录下创建一个CMakeLists.txt文件,用来编译生成静态库
```cmake
# 接受该子目录下的所有源文件
aux_source_directory(. SRCS)
# 生成静态库libmath
add_library(libmath ${SRCS})
```

2. 在根目录中创建CMakeLists.txt
```cmake
# cmake最低版本号要求
cmake_minimum_required (VERSION 2.8)

# 工程名
project (Demo4)


# 如果源文件太多一个个的写就不现实了,用aux_source_directory()函数,第一个参数表示在哪个目录下,参数二表示创建一个变量来接受该目录下的所有源文件
aux_source_directory(. SRCS)
# 把子文件中的源文件也添加进来,如果子目录

# 把子目录编译成静态库
# 指明本项目包含一个子目录 math，这样 math 目录下的 CMakeLists.txt 文件和源代码也会被处理 。
add_subdirectory(math)
# 生成可执行文件
add_executable(app ${SRCS} ${SRCS2})
# 使用链接库,将app和静态库链接起来
target_link_libraries(app libmath)
```

