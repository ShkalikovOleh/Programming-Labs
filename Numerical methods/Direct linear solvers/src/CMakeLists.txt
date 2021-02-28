cmake_minimum_required(VERSION 3.0)

project(DirectLSE LANGUAGES CXX)

set(src main.cpp)

include_directories(${PROJECT_SOURCE_DIR}/dlses)

add_executable(dlses ${src})
