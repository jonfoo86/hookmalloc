cmake_minimum_required(VERSION 2.6)

Set(TARGET hookm)
project(${TARGET} C)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -Wall -g -O3 ")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC -Wall -g -O0 ")

link_directories(/usr/local/lib /usr/local/lib64)
file(GLOB SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.c")
#include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")

# add dependencies
# include(CMakeLists-libconfuse.cmake)

# add output library
add_library(${TARGET} SHARED ${SOURCES})
#add_executable(${TARGET} ${SOURCES})
target_link_libraries(${TARGET} dl)



