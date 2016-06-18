cmake_minimum_required(VERSION 2.8)

project(relative_date CXX)

if(MSVC14 OR MSVC12)
    # has the support we need
else()
    include(CheckCXXCompilerFlag)
    CHECK_CXX_COMPILER_FLAG("-std=c++14" COMPILER_SUPPORTS_CXX14)
    CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
    if(COMPILER_SUPPORTS_CXX14)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
        set(CXX11SUPPORTED "1")
    elseif(COMPILER_SUPPORTS_CXX11)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
        set(CXX11SUPPORTED "1")
    else()
        message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support.")
    endif()
endif()

include_directories(include)

file(GLOB headers_ RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} include/relative_date.h)
file(GLOB sources_ RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} src/relative_date.cpp)
if (CXX11SUPPORTED)
    list(APPEND headers_ include/relative_date_cxx11.h)
    list(APPEND sources_ src/relative_date_cxx11.cpp)
endif()
source_group("" FILES ${headers_} ${sources_})

if (WIN32)
    add_definitions(-D_CRT_SECURE_NO_DEPRECATE)
    set(platformDir_ Win32)
else()
    set(platformDir_ Posix)
endif(WIN32)

add_library(relative_date STATIC ${headers_} ${sources_})

add_subdirectory(tests)
