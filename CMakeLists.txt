cmake_minimum_required (VERSION 2.6)
project (AssocArray)
set (CMAKE_CXX_COMPILER "g++-4.8")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
add_executable (tests tests.cpp)
