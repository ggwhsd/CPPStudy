cmake_minimum_required(VERSION 2.6)

project(muduoBaseTest)

add_definitions(-std=c++11)


link_directories(${PROJECT_SOURCE_DIR}/../lib)

add_executable(date_unittest Date_test.cc)
target_link_libraries(date_unittest muduo_base)

add_executable(logstream_unittest LogStream_test.cc)
target_link_libraries(logstream_unittest muduo_base boost_unit_test_framework)


add_executable(fileutil_test FileUtil_test.cpp)
target_link_libraries(fileutil_test muduo_base pthread)


add_executable(exception_test exception_test.cpp)
target_link_libraries(exception_test muduo_base pthread)