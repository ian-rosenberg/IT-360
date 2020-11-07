cmake_minimum_required(VERSION 3.7)

project(ex3)

#Edit these lines to point to your SDL2 libraries
set(SDL2_INCLUDE_DIR C:/SDL2Libs/MinGW/SDL2-2.0.12/include/SDL2)
set(SDL2_LIB_DIR C:/SDL2Libs/MinGW/SDL2-2.0.12/lib/x86)

find_package(OpenGL REQUIRED)

include_directories(${SDL2_INCLUDE_DIR})
link_directories(${SDL2_LIB_DIR})

set(SOURCES main.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} SDL2main SDL2 OpenGL::GL gl3w)