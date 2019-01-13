# 接受该目下的所有源文件,变量名不要和根目录中的变量名相同
aux_source_directory(. LIB_SRCS)
# 生成静态库libmath
add_library(libmath ${LIB_SRCS})

message("cache------>"${MY_CACHE_VALUE})

testFun()
testMacro()
message(fun---->${var_fun})
message(macro---->${var_macro})