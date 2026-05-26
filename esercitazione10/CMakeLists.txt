cmake_minimum_required(VERSION 3.20)
project(esercitazione10)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wshadow -Werror=vla")

# Trovo la libreria Eigen 
find_package(Eigen3 3.3 REQUIRED NO_MODULE)

add_executable(main main.cpp)
target_link_libraries(main PRIVATE Eigen3::Eigen)

add_test(NAME gradienteConiugato COMMAND main)

enable_testing()
