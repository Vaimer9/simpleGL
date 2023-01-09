cmake_minimum_required(VERSION 3.22)

project(main)

set(CMAKE_CXX_STANDARD 20)

set(SOURCES 
    src/shader.cpp
    src/utils.cpp
    src/window.cpp
    src/vao.cpp
    src/vbo.cpp
    src/shapes.cpp
    src/mesh.cpp
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
include_directories(include)
add_library(graphic SHARED ${SOURCES})

find_package (OpenGL REQUIRED)
target_link_libraries(graphic OpenGL::GL)
find_package (GLEW REQUIRED)
target_link_libraries(graphic GLEW::GLEW)
find_package (glfw3 REQUIRED)
target_link_libraries(graphic glfw)
