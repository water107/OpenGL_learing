CMAKE_MINIMUM_REQUIRED(VERSION 3.12)
project(OpenGL_lear)
set(CMAKE_CXX_STANDARD 17)

add_definitions(-DDEBUG)

file (GLOB ASSETS "./assets")
file (COPY ${ASSETS} DESTINATION ${CMAKE_BINARY_DIR})   # 把ASSETS放到二进制执行目录

include_directories(
    SYSTEM ${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/include   # CMAKE_CURRENT_SOURCE_DIR   工程的根目录
)

link_directories(
    SYSTEM ${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/lib
)

add_subdirectory(wrapper)
add_subdirectory(application)
add_subdirectory(glframework)

add_executable(OpenGL_lear "main.cpp" "glad.c")

target_link_libraries(OpenGL_lear glfw3.lib wrapper application fw)

