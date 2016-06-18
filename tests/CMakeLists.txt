cmake_minimum_required(VERSION 2.8)

project(tests CXX)

SET( CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -s" )
add_executable(relative_test relative_test.cpp)
target_link_libraries(relative_test relative_date)
