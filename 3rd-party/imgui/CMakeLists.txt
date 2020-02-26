cmake_minimum_required(VERSION 3.9)
project(OpenGLCustomTest)

add_library(imgui STATIC
        src/imgui.cpp
        src/imgui_impl_glfw.cpp
        src/imgui_impl_opengl3.cpp
        src/imgui_widgets.cpp
        src/imgui_draw.cpp)

target_compile_definitions(imgui PUBLIC IMGUI_IMPL_OPENGL_LOADER_GLAD)
target_include_directories(imgui PUBLIC include)
target_link_libraries(imgui PRIVATE glfw)
target_link_libraries(imgui PRIVATE glad)
