cmake_minimum_required(VERSION 3.21)

project("game"
    DESCRIPTION "Game with ECS Engine"
    VERSION 0.9.1
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME}
    main.cpp

    "src/ComponentManager.cpp"
    "src/Engine.cpp"
    "src/EntityManager.cpp"
    "src/SystemManager.cpp"
    
    "headers/ComponentCollection.hpp"
    "headers/ComponentManager.hpp"
    "headers/Engine.hpp"
    "headers/System.hpp"
    "headers/SystemManager.hpp"
 )
