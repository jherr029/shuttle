cmake_minimum_required (VERSION 3.1)

set(CMAKE_CXX_STANDARD 11)
set(GCC_COVERAGE_COMPILE_FLAGS "-g -O3")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../../bin")

project (shuttle)
add_subdirectory(src)
add_subdirectory(test)

enable_testing()
add_test(NAME testShuttle COMMAND shuttle)