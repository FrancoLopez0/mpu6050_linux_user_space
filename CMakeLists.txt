cmake_minimum_required(VERSION 3.16)

project(test_ioctl LANGUAGES C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(test_ioctl main.c)

set_target_properties(test_ioctl PROPERTIES
    C_STANDARD 11
    C_STANDARD_REQUIRED YES
    C_EXTENSIONS NO
)

target_link_libraries(test_ioctl PRIVATE i2c)

target_compile_options(test_ioctl PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)