# CMAKE总结
## 一.使用流程
1. 创建工程Demo
2. 在目录中编写CMakeLists.txt文件
3. 在Demo中创建目录build
4. 进入build目录,执行cmake ../生成makefile文件,执行make生成可执行文件  

*备注:之所以在build文件中执行cmake是为了将产生的所有中间文件都统一输出在build文件中,避免污染源文件,方便清理,这中方式叫外部构建,内部构建就是直接cmake .不创建build目录*
## 二.CMAKE基础知识
```cmake
#第一行要写cmake最低版本要求
cmake_minimum_required (VERSION 2.8)

#工程信息,project (Demo C),工程名及支持语言,默认不写语言,代表支持所有
project (Demo)

#打印信息,message()
#取变量${var_name}
#当project ()方法执行后就会创建两个全局变量,源文件目录名和二进制目录名
#以CMAKE\PROJECT\工程名打头都可以,结果是一样的
#内部构建时都指向Demo目录,外部构建二进制目录就指向外部构建目录build
message ("源文件目录:"${CMAKE_SOURCE_DIR})
message ("源文件目录:"${PROJECT_SOURCE_DIR})
message ("源文件目录:"${Demo_SOURCE_DIR})
message ("二进制文件目录:"${CMAKE_BINARY_DIR})
message ("二进制文件目录:"${PROJECT_BINARY_DIR})
message ("二进制文件目录:"${Demo_BINARY_DIR})

#为变量赋值,参数一:变量名,参数二变量值
set (var_name var_value)

#获取指定路径下的所有源文件,参数一:指定路径,参数二:用以接收所有文件名的变量
aux_sourcr_directory(path_name var_name)

#生成可执行文件,参数一:生成的可执行文件名,参数二:编译所需的所有源文件名
#多个源文件用空格分开,分号分开,双引号包住分开都是可以的
#结合aux_sourcr_directory(. SRCS),可以写成add_executable (exe_name ${SRCS})
add_executable (exe_name src_name)

#生成库文件,参数一:生成的库名,参数二:库类型,参数三:该库默认不会被编译,一般不用这个参数,参数四:所需源文件
add_library (lib_name [SHARED|STATIC|MODULE] [EXCLUDE_FROM_ALL] srcs)

#为当前工程Demo添加头文件目录,参数一:添加在前还是后,默认就是后,参数二:作为系统包含路径处理,一般不写,参数三就是要添加的头文件目录路径
include_directories ([AFTER|BEFORE] [SYSTEM] dirs)

#为指定工程添加头文件目录,一般是为子工程添加,参数一就是指定工程名,参数四:一般用PUBLIC
target_include_directories (target_name [SYSTEM] [AFTER|BEFORE] <PUBLIC|PRIVATE|INTERFACE> dirs)

#为当前工程链接库,参数是库文件的全路径,记住是全路径,所以并不常用
link_libraries (lib_path)

#为指定目标链接库,参数一:目标exe_name,参数二:库名,不需全路径
#如:target_link_libraries(app libmath)
target_link_libraries (target lib_name)

#设置目标属性,目前还不知道怎么用
set_target_properties(
    target1 target2 ... PROPERTIES 属性名称1 值 属性名称2 值 ...
)

#修改可执行文件输出位置
set(EXECUTABLE_OUTPUT_PATH "/users/yzy/")

#局部变量,就是cmakeLists.txt中创建的变量
set(VAR_NAME var_value)

#缓存变量,缓存变量是全局变量,持续化存储在CMakeCache.txt中
set(MY_CACHE_VALUE "cache_value" CACHE INTERNAL "这是描述")
set(my_global_string "string_value" CACHE STRING "这是字符串")
set(my_global_bool TRUE CACHE BOOL "这是布尔值")

#环境变量
#设置环境变量:
set(ENV{variable_name} value) 
#获取环境变量:
$ENV{variable_name}

#内置变量,也是全局变量
#EXECUTABLE_OUTPUT_PATH是CMake中的内置变量,CMake里面还包含大量的内置变量，和自定义的变量相同，常用的有以下: 
#CMAKE_C_COMPILER:指定C编译器 
#CMAKE_CXX_COMPILER:指定C++编译器 
#EXECUTABLE_OUTPUT_PATH:指定可执行文件的存放路径 
#LIBRARY_OUTPUT_PATH:指定库文件的放置路径 
#CMAKE_CURRENT_SOURCE_DIR:当前处理的CMakeLists.txt所在的路径
#CMAKE_BUILD_TYPE:控制构建的时候是Debug还是Release,命令:set(CMAKE_BUILD_TYPE Debug)
#CMAKE_SOURCR_DIR:无论外部构建还是内部构建，都指的是工程的顶层目录 (参考project命令执行之后，生成的_SOURCR_DIR以及CMake预定义的变量 PROJECT_SOURCE_DIR)
#CMAKE_BINARY_DIR:内部构建指的是工程顶层目录，外部构建指的是工程发 生编译的目录(参考project命令执行之后，生成的_BINARY_DIR以及CMake预 定义的变量PROJECT_BINARY_DIR)
#CMAKE_CURRENT_LIST_LINE:输出这个内置变量所在的行
```
## 三.CMAKE语法
```cmake
#基本控制语句
#if语句,endif中的条件对应第一个if中的条件
if(a)
    cmd1...
elseif(b)
    cmd2...
else(c)
    cmd3
endif(a)
#非真:空,0,N,NO,OFF,FALSE,NOTFOUND
#真:非空,1,Y,YES,ON,TRUE等等
#非:not

#常用语句
if (not exp) #与上面相反
if (var1 AND var2 #var1且var2都为真，条件成立
if (var1 OR var2) #var1或var2其中某一个为真，条件成立
if (COMMAND cmd) #如果cmd确实是命令并可调用，为真;
if (EXISTS dir) #如果目录存在，为真
if (EXISTS file) #如果文件存在，为真
if (file1 IS_NEWER_THAN file2) #当file1比file2新，或file1/file2中有一个 不存在时为真，文件名需使用全路径
if (IS_DIRECTORY dir) #当dir是目录时，为真 
if (DEFINED var) #如果变量被定义，为真
if (string MATCHES regex) #当给定变量或字符串能匹配正则表达式regex时，为真
#数字表达式
if (var LESS number) #var小于number为真
if (var GREATER number) #var大于number为真 
if (var EQUAL number) #var等于number为真
#字母表顺序比较
IF (var1 STRLESS var2) #var1字母顺序小于var2为真
IF (var1 STRGREATER var2) #var1字母顺序大于var2为真 
IF (var1 STREQUAL var2) #var1和var2字母顺序相等为真

#while循环,基本可参考if语句
while(a)
    cmd
endwhile(a)

#foreach循环,迭代循环
foreach(src ${SRCS})
    message(src--->${src})
endforeach(src ${SRCS})

#foreach循环,范围循环,0可以省略,默认0开始
foreach(var RANGE 0 100)
    message(${var})
endforeach(var RANGE 0 100)

#foreach步进循环,步长为10,有步长的时候开始数要写
foreach(var RANGE 0 100 10)
    message(${var})
endforeach(var RANGE 0 100 10)
```
## 构建范围及属性
```cmake
target_include_directories() #Include的头文件的查找目录，也就是Gcc的[-Idir...]选项
target_compile_definitions() #通过命令行定义的宏变量
target_compile_options() #gcc其他的一些编译选项指定，比如-fPIC

#以上的额三个命令会生成INCLUDE_DIRECTORIES, COMPILE_DEFINITIONS, COMPILE_OPTIONS变量的值或者INTERFACE_INCLUDE_DIRECTORIES,INTERFACE_COMPILE_DEFINITIONS,INTERFACE_COMPILE_OPTIONS的值.
#这三个命令都有三种可选模式: PRIVATE, PUBLIC。 INTERFACE. PRIVATE模式仅填充 不是接口的目标属性; INTERFACE模式仅填充接口目标的属性.PUBLIC模式填充这两种 的目标属性。
```
## 宏和函数
```cmake
#cmake中可以定义函数function和宏micro,这里的宏不是c中的宏,暂且叫宏函数吧
#function和micro最大的区别在于里面的变量,function内部的变量外部访问不到,而micro里面的变量是全局的
#定义一个function
function(testFun)
    set(var_fun "i am fun")    
endfunction(testFun)
#定义一个macro
macro(testMacro)
    set(var_macro "i am macro")
endmacro(testMacro)
#调用函数和宏函数
testFun()
testMacro()
message(fun---->${var_fun})#为空,因为访问不到var_fun
message(macro---->${var_macro})#不为空,访问到了

```
