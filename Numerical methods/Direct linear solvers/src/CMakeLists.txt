cmake_minimum_required(VERSION 3.1)

project(DirectLSE LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

set(src main.cpp)

include_directories(${PROJECT_SOURCE_DIR}/dlses)

enable_testing()
add_subdirectory(test)

add_executable(dlses ${src})
