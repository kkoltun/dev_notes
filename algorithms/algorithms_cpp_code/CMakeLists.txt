cmake_minimum_required(VERSION 3.3)
project(algorithms_cpp_code)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

add_subdirectory(gtests)

find_package(Threads REQUIRED)
enable_testing()
include_directories(${GTEST_SOURCE_DIR}/include ${GTEST_SOURCE_DIR})

file(GLOB SOURCES "src/*.h" "src/*.cpp" "src/sorting/*.h" "src/sorting/*.cpp" "src/dac/*.h" "src/dac/*.cpp" "src/structures/*.h" "src/structures/*.cpp" "src/graphs/*.h" "src/graphs/*.cpp")
file(GLOB TEST_SOURCES "tests/sorting/*.cpp" "tests/dac/*.cpp" "tests/structures/*.cpp" "tests/graphs/*.cpp")
add_executable(runAllTests tests.cpp ${TEST_SOURCES} ${SOURCES}
        tests/sorting/mergeSortTest.cpp tests/sorting/heapSortTest.cpp tests/sorting/insertSortTest.cpp tests/sorting/quickSortTest.cpp tests/sorting/countingSortTest.cpp tests/sorting/bucketSortTest.cpp
        tests/dac/findMaxSubarrayTest.cpp
        tests/structures/queueTest.cpp tests/structures/doublyLinkedListTest.cpp tests/structures/circularDoublyLinkedListTest.cpp
        tests/graphs/bfsTest.cpp tests/graphs/dfsTest.cpp tests/graphs/topologicalSortTest.cpp)
add_executable(algorithms_cpp_code main.cpp ${SOURCES}
        src/sorting/mergeSort.cpp src/structures/Heap.cpp src/structures/Heap.h src/sorting/heapSort.h src/sorting/heapSort.cpp src/sorting/quickSort.cpp src/sorting/quickSort.h src/sorting/mergeSort2.cpp src/sorting/mergeSort2.h src/sorting/countingSort.cpp src/sorting/countingSort.h src/sorting/bucketSort.cpp src/sorting/bucketSort.h
        src/dac/findMaxSubarray.cpp src/dac/findMaxSubarray.h
        src/structures/Queue.cpp src/structures/Queue.h src/structures/DoublyLinkedList.h src/structures/CircularDoublyLinkedList.h src/structures/Node.cpp src/structures/Node.h
        src/graphs/Vertex.cpp src/graphs/Vertex.h src/graphs/bfs.h src/graphs/bfs.cpp src/graphs/dfs.h src/graphs/dfs.cpp src/graphs/DfsVertex.cpp src/graphs/DfsVertex.h src/graphs/topologicalSort.cpp src/graphs/topologicalSort.h src/graphs/transpose.h src/graphs/transpose.cpp)

target_link_libraries(runAllTests gtest gtest_main)
add_test(AllTests runAllTests)