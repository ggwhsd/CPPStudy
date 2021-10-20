cmake_minimum_required(VERSION 2.6)
message("hello")
project(muduoStudy)

add_definitions(-std=c++11)

message(${PROJECT_NAME})

set(base_SRCS
  Date.cc
  TimeZone.cpp
  LogStream.cc
  CurrentThread.cpp
  Logging.cpp
  FileUtil.cpp
  Timestamp.cpp
  Condition.cpp
  Exception.cpp
  ProcessInfo.cpp
  LogFile.cpp
  CountDownLatch.cpp
  Thread.cpp
  ThreadPool.cpp
  AsyncLogging.cpp
  )
#AUX_SOURCE_DIRECTORY(. SRC_LIST)

#生成库
add_library(muduo_base ${base_SRCS})
#生成的库依赖于添加第三方标准库
target_link_libraries(muduo_base pthread rt)
#安装生成的库到当前lib目录下，在执行make install时执行
install(TARGETS muduo_base 
ARCHIVE DESTINATION ${PROJECT_SOURCE_DIR}/lib
LIBRARY DESTINATION ${PROJECT_SOURCE_DIR}/libso
)


#ADD_EXECUTABLE(Date_test ./test/Date_test.cc ${SRC_LIST})