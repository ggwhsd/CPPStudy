# CMakeList.txt: CMakeProject1 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)
set(CMAKE_CXX_STANDARD 11)
message("系统自动生成变量: " ${CMakeProject1_SOURCE_DIR})
message("系统自动生成变量: " ${CMakeProject1_BINARY_DIR})
message("默认文件输出路径Debug:${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG}")
message("默认文件输出路径Release:${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE}")



# 将源代码添加到此项目的可执行文件。 默认控制台工程，这也是我们常用的后台程序的工程。
add_executable (CMakeProject1 "CMakeProject1.cpp" "CMakeProject1.h" "v.cpp" "v.h"  "sub/c.cpp")

target_link_libraries(CMakeProject1 "myLibTwo" "myLibOne")



# TODO: 如有需要，请添加测试并安装目标。
IF( NOT(CMAKE_SYSTEM_NAME MATCHES "Windows" ))
	message("${CMAKE_SYSTEM_NAME} add pthread")
   target_link_libraries(CMakeProject1 pthread)
Endif()
IF( CMAKE_SYSTEM_NAME MATCHES "Windows" )
	message(${CMAKE_SYSTEM_NAME})
Endif()


