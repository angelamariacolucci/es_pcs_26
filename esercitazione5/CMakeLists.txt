cmake_minimum_required(VERSION 3.20)
project(esercitazione5)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wshadow -Werror=vla")

# Target principale: misura dei tempi
set(SRC_measure_sort2 timecounter.cpp measure_sort2.cpp)
add_executable(measure_sort2 ${SRC_measure_sort2})

# Target per i test unitari
add_executable(test_bubblesort test_bubblesort.cpp)
add_test(NAME bubblesort COMMAND test_bubblesort)

add_executable(test_insertionsort test_insertionsort.cpp)
add_test(NAME insertionsort COMMAND test_insertionsort)

add_executable(test_selectionsort test_selectionsort.cpp)
add_test(NAME selectionsort COMMAND test_selectionsort)

add_executable(test_mergesort test_mergesort.cpp)
add_test(NAME mergesort COMMAND test_mergesort)

add_executable(test_quicksort test_quicksort.cpp)
add_test(NAME quicksort COMMAND test_quicksort)

add_executable(test_quicksort_hybrid test_quicksort_hybrid.cpp)
add_test(NAME quicksort_hybrid COMMAND test_quicksort_hybrid)

enable_testing()