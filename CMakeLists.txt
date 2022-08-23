cmake_minimum_required(VERSION 3.22)

project(main)

set(CMAKE_CXX_STANDARD 17)

add_executable(main main.cpp)

find_package ( OpenGL REQUIRED )
target_link_libraries(main OpenGL::GL )

find_package ( GLEW REQUIRED )
target_link_libraries(main GLEW::GLEW )

find_package ( glfw3 REQUIRED )
target_link_libraries(main glfw )
