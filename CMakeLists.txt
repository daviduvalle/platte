cmake_minimum_required(VERSION 3.7)

add_definitions(-std=c++17)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")
set(CMAKE_BUILD_TYPE Debug)

project(Platte)

include_directories(include)
file(GLOB SOURCES "src/*.cpp")

add_executable(Platte ${SOURCES})
