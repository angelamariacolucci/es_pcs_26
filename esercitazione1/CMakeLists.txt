cmake_minimum_required(VERSION 3.20)

project(esercitazione1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wshadow")
set(SOURCES media_t.cpp)
add_executable(esercitazione1 media_t.cpp)
add_executable(argc_argv argc_argv.cpp)
