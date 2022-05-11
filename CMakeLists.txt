cmake_minimum_required(VERSION 3.20)

project("game"
    DESCRIPTION "Game with ECS Engine"
    VERSION 0.9.1
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

## If you want to link SFML statically
set(SFML_STATIC_LIBRARIES TRUE)

## In most cases better set in the CMake cache
set(SFML_DIR "SFML-2.5.1/lib/cmake/SFML")

include_directories("SFML-2.5.1/include")

find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)

add_executable(${PROJECT_NAME}
    main.cpp

    "src/ComponentManager.cpp"
    "src/Engine.cpp"
    "src/EntityManager.cpp"
    "src/SystemManager.cpp"
    "src/ThreadPool.cpp"
    "src/Transform.cpp"
    
    "headers/ComponentCollection.hpp"
    "headers/ComponentManager.hpp"
    "headers/Engine.hpp"
    "headers/System.hpp"
    "headers/SystemManager.hpp")

target_link_libraries(${PROJECT_NAME} sfml-system sfml-window sfml-graphics)