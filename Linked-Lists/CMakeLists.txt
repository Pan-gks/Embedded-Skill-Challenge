cmake_minimum_required(VERSION 3.12.0)
project(Linked-Lists)

set(CMAKE_C_STANDARD 99)

include_directories(include)

file(GLOB SOURCES "src/*.c")
add_library(linked_lists STATIC ${SOURCES})



enable_testing()
add_executable(test_linked_lists test/test_linked_lists.c)
target_link_libraries(test_linked_lists linked_lists pthread)
add_test(NAME linked_lists_test COMMAND test_linked_lists)
