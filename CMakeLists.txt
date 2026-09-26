cmake_minimum_required(VERSION 3.16)

project(mpu6050 LANGUAGES C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(mpu6050 
    main.c
    mpu6050.c
)

set_target_properties(mpu6050 PROPERTIES
    C_STANDARD 11
    C_STANDARD_REQUIRED YES
    C_EXTENSIONS NO
)

target_link_libraries(mpu6050 PRIVATE
    i2c
    m
)

target_compile_options(mpu6050 PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)