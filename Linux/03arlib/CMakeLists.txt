
cmake_minimum_required(VERSION 2.6)
project(hello_library)
# 根据库文件代码生成静态库
add_library(hello_library STATIC libhello.c)
# 包含指定头文件所在的目录
target_include_directories(hello_library PUBLIC  ./)

# 创建可执行程序
add_executable(hello_binary usehello.c)
# 链接静态库文件
target_link_libraries( hello_binary PRIVATE hello_library)
