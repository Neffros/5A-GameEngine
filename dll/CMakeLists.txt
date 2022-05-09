cmake_minimum_required(VERSION 3.21)
project(5A_GameEngine_Lib)

set(CMAKE_CXX_STANDARD 20)
add_library(5A_GameEngine_Lib SHARED library.cpp)
IF(CMAKE_BUILD_TYPE MATCHES Debug)
    SET(MODE debug)
ELSE(CMAKE_BUILD_TYPE MATCHES Debug)
    SET(MODE release)
ENDIF(CMAKE_BUILD_TYPE MATCHES Debug)

message(${MODE})

add_custom_command(TARGET 5A_GameEngine_Lib POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        "${PROJECT_SOURCE_DIR}/cmake-build-${MODE}/5A_GameEngine_Lib.dll"
        "${PROJECT_SOURCE_DIR}/../exe/cmake-build-${MODE}")

add_custom_command(TARGET 5A_GameEngine_Lib POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        "${PROJECT_SOURCE_DIR}/cmake-build-${MODE}/5A_GameEngine_Lib.lib"
        "${PROJECT_SOURCE_DIR}/../exe/cmake-build-${MODE}")
