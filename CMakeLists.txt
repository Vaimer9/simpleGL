cmake_minimum_required(VERSION 3.22)

project(simpleGL)

set(CMAKE_CXX_STANDARD 20)

set(SOURCES 
    src/shader.cpp
    src/color.cpp
    src/utils.cpp
    src/window.cpp
    src/vao.cpp
    src/vbo.cpp
    src/texture.cpp
    src/shapes.cpp
    src/mesh.cpp
    src/logger.cpp
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
include_directories(include)
add_library(${PROJECT_NAME} SHARED ${SOURCES})

find_package (OpenGL REQUIRED)
target_link_libraries(${PROJECT_NAME} OpenGL::GL)
find_package (GLEW REQUIRED)
target_link_libraries(${PROJECT_NAME} GLEW::GLEW)
find_package (glfw3 REQUIRED)
target_link_libraries(${PROJECT_NAME} glfw)
