cmake_minimum_required(VERSION 3.23)
project(noteUtils)

set(CMAKE_CXX_STANDARD 20)

include_directories(.)

add_executable(readmeMaker src/readmeMaker.cpp)
add_executable(noteMaker src/noteMaker.cpp)
