cmake_minimum_required(VERSION 3.3)
project(algorithms_cpp_code)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

add_subdirectory(gtests)

find_package(Threads REQUIRED)
enable_testing()
include_directories(${GTEST_SOURCE_DIR}/include ${GTEST_SOURCE_DIR})

file(GLOB SOURCES "src/*.h" "src/*.cpp" "src/sorting/*.h" "src/sorting/*.cpp")
file(GLOB TEST_SOURCES "tests/*.cpp")
add_executable(runAllTests tests.cpp ${TEST_SOURCES} ${SOURCES} tests/mergeSortTest.cpp tests/heapSortTest.cpp tests/heapSortTest.h)
add_executable(algorithms_cpp_code main.cpp ${SOURCES} src/sorting/mergeSort.cpp src/sorting/Heap.cpp src/sorting/Heap.h src/sorting/heapSort.h src/sorting/heapSort.cpp)

target_link_libraries(runAllTests gtest gtest_main)
add_test(AllTests runAllTests)