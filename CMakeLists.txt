cmake_minimum_required(VERSION 3.7)
project(PAMSI_First)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Node.cpp)
add_executable(PAMSI_First ${SOURCE_FILES})