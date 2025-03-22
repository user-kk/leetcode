add_executable(thread_pool_test main.cpp)
target_include_directories(thread_pool_test PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(thread_pool_test PRIVATE fmt::fmt cpptrace::cpptrace nlohmann_json::nlohmann_json)
target_compile_options(thread_pool_test PRIVATE -fsanitize=address -fno-omit-frame-pointer -fsanitize-recover=address)
target_link_options(thread_pool_test PRIVATE -fsanitize=address)
set_target_properties(thread_pool_test PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)