cmake_minimum_required(VERSION 3.10)

project(yawc C)
include_directories(include)

file(GLOB SOURCES "src/*.c")

add_executable(yawc ${SOURCES})
target_link_libraries(yawc m)
