# CMakeList.txt: 顶层 CMake 项目文件，在此处执行全局配置
# 并包含子项目。
#
cmake_minimum_required (VERSION 3.8)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
message("ddd "  ${ABC} " " ${BCD})
project ("CMakeProject1")

 
IF (CMAKE_SYSTEM_NAME MATCHES "Windows")
	ADD_DEFINITIONS(-DDLL_EXPORTS)

	message("Debug编译模式:" ${CMAKE_CXX_FLAGS_DEBUG})  #默认在debug下是MDd
	message("Release编译模式:" ${CMAKE_CXX_FLAGS_RELEASE}) 
	#ADD_DEFINITIONS(-D_UNICODE)
	message("字节模式:" ${_UNICODE})  #默认是多字节

	#set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MD")
#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MDd")
ENDIF()

#引入某个目录下的所有源文件到变量otherProject_src_files中，无法包含头文件
#aux_source_directory("./otherProject/src" otherProject_src_files)


#引入头文件目录，相当于VC++目录，后续在项目中，就无需指定路径，就可以直接include对应文件，这个是针对所有项目都有效。
#include_directories("../otherProject/include")

#一般子项目中无需包含头文件，但是如果希望通过cmake生成的子项目中包含第三方头文件，而且只想在某个子项目中使用，则可以使用如下方式,这在引入一些只有头文件的库。
#file(GLOB_RECURSE lib_headers "./otherProject/src/*.h")
#add_library(target ${lib_headers})



#如下一段设置，用于自定义输出路径，可执行程序的路径，以及动态库的路径。我这里没有使用，只是放在这。
# 64位
if (CMAKE_CL_64)
    # 设置 可执行程序输出目录
	set(publish_bin_debug 			${CMAKE_CURRENT_SOURCE_DIR}/publish/x64/bin/debug64)
	set(publish_bin_release 		${CMAKE_CURRENT_SOURCE_DIR}/publish/x64/bin/release64)

    # 设置库文件输出目录
	set(publish_lib_debug 			${CMAKE_CURRENT_SOURCE_DIR}/publish/x64/lib/debug64)
	set(publish_lib_release 		${CMAKE_CURRENT_SOURCE_DIR}/publish/x64/lib/release64)

	#set(PROJECT_NAME 				${PROJECT_NAME}64)
# 32
else()
 # 设置 可执行程序输出目录
	set(publish_bin_debug 			${CMAKE_CURRENT_SOURCE_DIR}/publish/x86/bin/debug)
	set(publish_bin_release 		${CMAKE_CURRENT_SOURCE_DIR}/publish/x86/bin/release)

 # 设置库文件输出目录
	set(publish_lib_debug 			${CMAKE_CURRENT_SOURCE_DIR}/publish/x86/lib/debug)
	set(publish_lib_release 		${CMAKE_CURRENT_SOURCE_DIR}/publish/x86/lib/release)
endif()

## 指定可执行程序输出目录
		#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG 	${publish_bin_debug})
		#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE 	${publish_bin_release})
# 指定 库文件输出目录
		#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG 	${publish_lib_debug})
		#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RLEASE 	${publish_lib_release})



# 包含子项目。
add_subdirectory ("CMakeProject1")

add_subdirectory("myLibOne")

add_subdirectory("myLibTwo")
