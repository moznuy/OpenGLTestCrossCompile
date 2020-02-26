cmake_minimum_required(VERSION 3.8)
project(OpenGLCustomTest)

set(CMAKE_CXX_STANDARD 14)

add_executable(OpenGLCustomTest main.cpp)

# GLAD
add_subdirectory(3rd-party/glad)
target_link_libraries(OpenGLCustomTest PRIVATE glad)

# GLFW
add_subdirectory(3rd-party/glfw)
target_link_libraries(OpenGLCustomTest PRIVATE glfw)