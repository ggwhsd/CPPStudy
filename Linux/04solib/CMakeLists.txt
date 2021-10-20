cmake_minimum_required(VERSION 2.6)

message("**********************")

project(hello_library)

message(${PROJECT_NAME})
message(${PROJECT_SOURCE_DIR})
# 根据库文件代码生成动态库
add_library(hello_library SHARED  libhello.c)

# 创建动态库别名
add_library(hello::library ALIAS hello_library)

# 包含指定头文件所在的目录
target_include_directories(hello_library PUBLIC  ./)

# 创建可执行程序
add_executable(hello_binary usehello.c)

# 链接静态库文件
target_link_libraries( hello_binary PRIVATE hello::library)
