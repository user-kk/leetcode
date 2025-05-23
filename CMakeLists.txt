cmake_minimum_required(VERSION 3.10)
project(leetcode)

set(CXX_STANDARD 23)
set(CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
if(NOT DEFINED CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug) #Release
endif()


find_package(GTest REQUIRED)
find_package(fmt REQUIRED)
find_package(cpptrace REQUIRED)
find_package(nlohmann_json REQUIRED)
find_package(asio REQUIRED)



include(GoogleTest)

enable_testing()




# 获取test文件夹下所有的.cpp文件
file(GLOB TEST_SOURCES CONFIGURE_DEPENDS "test/*.cpp")

# 为每个.cpp文件生成对应的可执行文件
# foreach(TEST_SOURCE ${TEST_SOURCES})
#     get_filename_component(TEST_NAME ${TEST_SOURCE} NAME_WE)
#     add_executable(${TEST_NAME}_test ${TEST_SOURCE})
#     target_include_directories(${TEST_NAME}_test PRIVATE include)
#     target_link_libraries(${TEST_NAME}_test PRIVATE gtest gtest_main)
#     gtest_discover_tests(${TEST_NAME}_test)   
# endforeach(TEST_SOURCE)

#遍历源码文件获取文件名逐以重定义宏
foreach(source ${TEST_SOURCES})   
	get_filename_component(file_name ${source} NAME_WE)   
	set_source_files_properties(${source} PROPERTIES COMPILE_DEFINITIONS
	"CURRENT_FILE=${file_name}")  
endforeach()

#生成可执行文件
add_executable(lc_test ${TEST_SOURCES})
target_compile_features(lc_test PRIVATE cxx_std_23)
target_compile_definitions(lc_test PRIVATE TEST_DATA_PATH="${CMAKE_SOURCE_DIR}/test/data")


#设置头文件
target_include_directories(lc_test PRIVATE include)
target_link_libraries(lc_test PRIVATE gtest gtest_main fmt::fmt cpptrace::cpptrace nlohmann_json::nlohmann_json asio::asio)
target_compile_options(lc_test PRIVATE -fsanitize=address -fno-omit-frame-pointer -fsanitize-recover=address)
target_link_options(lc_test PRIVATE -fsanitize=address)


#设置ctest命令
gtest_discover_tests(lc_test)


add_subdirectory(${CMAKE_SOURCE_DIR}/project)

