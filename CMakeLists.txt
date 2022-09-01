cmake_minimum_required(VERSION 3.23)
project(noteUtils)

set(CMAKE_CXX_STANDARD 20)
find_package(Catch2 3 REQUIRED)

include_directories(.)

add_executable(readmeMaker src/readmeMaker.cpp src/StringManipulators.cpp)
add_executable(noteMaker src/noteMaker.cpp src/StringManipulators.cpp)
add_executable(Tests src/unitTests.cpp src/StringManipulators.cpp)
target_link_libraries(Tests PRIVATE Catch2::Catch2WithMain)
