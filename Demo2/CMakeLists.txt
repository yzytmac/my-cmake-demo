# cmake最低版本号要求
cmake_minimum_required (VERSION 2.8)

# 工程名
project (Demo2)

# 生成可执行文件,参数一可执行文件名,后面的参数是需要的源文件
# add_executable(app main.c MathFunction.c)
# 如果源文件太多一个个的写就不现实了,用aux_source_directory()函数,第一个参数表示在哪个目录下,参数二表示创建一个变量来接受该目录下的所有源文件
aux_source_directory(. SRCS)
add_executable(app ${SRCS})