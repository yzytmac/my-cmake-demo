# cmake最低版本号要求
cmake_minimum_required (VERSION 2.8)

# 工程名
project (Demo4)

# 生成可执行文件,参数一可执行文件名,后面的参数是需要的源文件
# add_executable(app main.c MathFunction.c)
# 如果源文件太多一个个的写就不现实了,用aux_source_directory()函数,第一个参数表示在哪个目录下,参数二表示创建一个变量来接受该目录下的所有源文件
aux_source_directory(. SRCS)
# 把子文件中的源文件也添加进来,如果子目录很多这样不好
#aux_source_directory(./math SRCS2)

# 把子目录编译成静态库
# 指明本项目包含一个子目录 math，这样 math 目录下的 CMakeLists.txt 文件和源代码也会被处理 。
add_subdirectory(math)
add_executable(app ${SRCS} ${SRCS2})
# 使用链接库,将app和静态库链接起来
target_link_libraries(app libmath)