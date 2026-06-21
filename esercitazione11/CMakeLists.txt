cmake_minimum_required(VERSION 3.20)
project(cicli_minimi CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wshadow -Werror=vla")

include_directories(include)

enable_testing()
add_executable(test_cicliDFS test_cicliDFS.cpp)
add_test(NAME cicliDFS COMMAND test_cicliDFS)

add_executable(test_DePina test_DePina.cpp)
add_test(NAME DePina COMMAND test_DePina)
