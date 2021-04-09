cmake_minimum_required(VERSION 3.0)

project(opengl)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp ./include/glad.c)

add_executable(opengl ${SOURCE_FILES})

Target_link_libraries(opengl glfw dl)

# install(TARGETS opengl RUNTIME DESTINATION bin)
