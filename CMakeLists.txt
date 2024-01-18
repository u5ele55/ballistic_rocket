cmake_minimum_required (VERSION 3.10)
project(ballistic_rocket)

file(GLOB UTILS utils/*/*/*.cpp utils/*/*.cpp utils/*.cpp)
file(GLOB BR ballistic_rocket/*/*.cpp)
file(GLOB GLBL global/*.cpp)

add_executable(run 
    main.cpp
    ${UTILS}
    ${BR}
    ${GLBL}
    )
