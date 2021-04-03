cmake_minimum_required(VERSION 3.6)

project(langy)

include_directories(src/include)
file(GLOB SOURCES "src/*.cpp")
add_executable(langy ${SOURCES})
