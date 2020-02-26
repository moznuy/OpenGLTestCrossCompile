cmake_minimum_required(VERSION 3.8)
project(glad)

set(CMAKE_CXX_STANDARD 14)

# GLAD
add_library(glad src/glad.c)
target_include_directories(glad PUBLIC include)
