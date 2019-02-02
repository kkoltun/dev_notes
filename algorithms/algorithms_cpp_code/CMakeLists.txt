cmake_minimum_required(VERSION 3.3)
project(algorithms_cpp_code)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

add_subdirectory(gtests)

find_package(Threads REQUIRED)
enable_testing()
include_directories(${GTEST_SOURCE_DIR}/include ${GTEST_SOURCE_DIR})

file(GLOB SOURCES "src/*.h" "src/*.cpp" "src/sorting/*.h" "src/sorting/*.cpp" "src/dac/*.h" "src/dac/*.cpp")
file(GLOB TEST_SOURCES "tests/sorting/*.cpp" "tests/dac/*.cpp")
add_executable(runAllTests tests.cpp ${TEST_SOURCES} ${SOURCES} tests/sorting/mergeSortTest.cpp tests/sorting/heapSortTest.cpp tests/sorting/insertSortTest.cpp tests/sorting/quickSortTest.cpp tests/sorting/countingSortTest.cpp)
add_executable(algorithms_cpp_code main.cpp ${SOURCES} src/sorting/mergeSort.cpp src/sorting/Heap.cpp src/sorting/Heap.h src/sorting/heapSort.h src/sorting/heapSort.cpp src/sorting/quickSort.cpp src/sorting/quickSort.h src/sorting/mergeSort2.cpp src/sorting/mergeSort2.h src/dac/findMaxSubarray.cpp src/dac/findMaxSubarray.h tests/dac/findMaxSubarrayTest.cpp src/sorting/countingSort.cpp src/sorting/countingSort.h)

target_link_libraries(runAllTests gtest gtest_main)
add_test(AllTests runAllTests)