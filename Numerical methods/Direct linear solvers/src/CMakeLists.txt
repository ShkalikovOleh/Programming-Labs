cmake_minimum_required(VERSION 3.1)

project(DirectLSE LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

include_directories(${PROJECT_SOURCE_DIR}/dlses)

enable_testing()
add_subdirectory(test)

add_executable(dlses main.cpp)

add_executable(hw2 hw2.cpp)
