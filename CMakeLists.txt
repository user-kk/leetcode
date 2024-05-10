cmake_minimum_required(VERSION 3.10)
project(leetcode)

set(CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
if(NOT DEFINED CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug) #Release
endif()


find_package(GTest REQUIRED)

enable_testing()

# 获取test文件夹下所有的.cpp文件
file(GLOB_RECURSE TEST_SOURCES CONFIGURE_DEPENDS "test/*.cpp")

# 为每个.cpp文件生成对应的可执行文件
foreach(TEST_SOURCE ${TEST_SOURCES})
    get_filename_component(TEST_NAME ${TEST_SOURCE} NAME_WE)
    add_executable(${TEST_NAME}_test ${TEST_SOURCE})
    target_include_directories(${TEST_NAME}_test PRIVATE include)
    target_link_libraries(${TEST_NAME}_test PRIVATE gtest gtest_main)
    add_test(NAME ${TEST_NAME}_test COMMAND ${TEST_NAME}_test)    
endforeach(TEST_SOURCE)