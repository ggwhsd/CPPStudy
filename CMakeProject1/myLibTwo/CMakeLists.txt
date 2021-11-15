
message("myLibTwo 输出路径:" ${CMAKE_CURRENT_BINARY_DIR})
# file 实现copy某个文件到另一个路径下，这里为了演示才做这一步，实际上可以通过设置生成路径的方式，将所有dll文件全都生成到某个路径中
IF (CMAKE_SYSTEM_NAME MATCHES "Windows")

	file(COPY ${CMAKE_CURRENT_BINARY_DIR}/Debug/myLibTwo.dll DESTINATION ${CMakeProject1_BINARY_DIR}/${PROJECT_NAME}/Debug/)

ENDIF()
add_library(myLibTwo SHARED "myLibTwo.cpp" "myLibTwo.h")
