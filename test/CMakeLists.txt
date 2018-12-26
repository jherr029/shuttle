configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
                 ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
                 EXCLUDE_FROM_ALL)


# include_directories(${PROJECT_SOURCE_DIR}/include)
add_library(CurlT ../src/curl.cpp ../include/curl.h)
add_library(JsonT ../src/jsonParse.cpp ../include/jsonParse.h)
add_library(DMCT ../src/distanceMatrixCell.cpp ../include/distanceMatrixCell.h)
add_library(DMT ../src/distanceMatrix.cpp ../include/distanceMatrix.h)
add_executable(tests main.cpp )
target_link_libraries(tests gtest_main pthread CurlT JsonT DMCT DMT curl)