find_package(liburing REQUIRED)

add_executable(io_uring_test main.cpp)
target_include_directories(io_uring_test PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(io_uring_test PRIVATE fmt::fmt cpptrace::cpptrace nlohmann_json::nlohmann_json liburing::liburing spdlog::spdlog)
target_compile_options(io_uring_test PRIVATE -fsanitize=address -fno-omit-frame-pointer -fsanitize-recover=address)
target_link_options(io_uring_test PRIVATE -fsanitize=address)
set_target_properties(io_uring_test PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)