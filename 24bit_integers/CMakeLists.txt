cmake_minimum_required(VERSION 3.12.0)
project(24bit_integers)

set(CMAKE_C_STANDARD 99)

include_directories(include)

enable_testing()
add_library(converter STATIC src/converter.c)
add_executable(conversion_test test/test_conversion.c)
target_link_libraries(conversion_test converter)
add_test(NAME conversion_test COMMAND conversion_test)
