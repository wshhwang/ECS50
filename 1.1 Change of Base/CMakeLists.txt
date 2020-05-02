cmake_minimum_required(VERSION 3.15)
project(Homework_1_1)

set(CMAKE_CXX_STANDARD 14)

add_executable(Homework_1_1        changeOfBase.cpp)
target_compile_options(ECS50 PRIVATE -Wall -Wextra -Werror)