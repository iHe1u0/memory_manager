cmake_minimum_required(VERSION 3.5.0)

project(MemChkLib VERSION 1.0.0 LANGUAGES C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)

include_directories(${CMAKE_SOURCE_DIR}/include/)

file(GLOB_RECURSE SRC_DIR_LIST
  "${CMAKE_SOURCE_DIR}/include/*.h"
  "${CMAKE_SOURCE_DIR}/include/*.inl"
  "${CMAKE_SOURCE_DIR}/src/*.cpp")

add_library(${PROJECT_NAME} STATIC ${SRC_DIR_LIST})

message(STATUS "SRC_DIR_LIST = ${SRC_DIR_LIST}")