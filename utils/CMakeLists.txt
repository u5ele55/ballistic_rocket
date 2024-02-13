file(GLOB SOURCES *.cpp)
file(GLOB HEADERS *.hpp)
add_library(utils ${HEADERS} ${SOURCES})