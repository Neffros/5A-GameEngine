cmake_minimum_required(VERSION 3.21)
project(5A_GameEngine)

set(CMAKE_CXX_STANDARD 20)
add_compile_definitions(DllExport)
include_directories(../dll)
add_executable(5A_GameEngine main.cpp)
target_link_libraries(5A_GameEngine 5A_GameEngine_Lib)
