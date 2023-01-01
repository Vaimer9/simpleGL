cmake_minimum_required(VERSION 3.22)

project(main)

set(CMAKE_CXX_STANDARD 20)

set(SOURCES 
    src/main.cpp
    src/shader.cpp
    src/utils.cpp
    src/window.cpp
    src/targets.cpp
    src/vao.cpp
    src/vbo.cpp
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
include_directories(include)
add_executable(main ${SOURCES})

find_package (OpenGL REQUIRED)
target_link_libraries(main OpenGL::GL)

find_package (GLEW REQUIRED)
target_link_libraries(main GLEW::GLEW)

find_package (glfw3 REQUIRED)
target_link_libraries(main glfw)
