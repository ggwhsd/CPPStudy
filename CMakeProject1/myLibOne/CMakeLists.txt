
message("系统自动生成变量: " ${myLibOne_SOURCE_DIR})
message("系统自动生成变量: " ${myLibOne_BINARY_DIR})
message("默认文件输出路径Debug:${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG}")
message("默认文件输出路径Release:${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE}")

add_library(myLibOne STATIC "myLibOne.cpp" "myLibOne.h" "log.h")
