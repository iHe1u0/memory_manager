cmake_minimum_required(VERSION 3.5.0)

project(MemChk VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)

add_compile_options(-DDEBUG)

include_directories(${CMAKE_SOURCE_DIR}/include/)

add_subdirectory(${CMAKE_SOURCE_DIR}/src/)

add_executable(MemChk main.cpp)

target_link_libraries(MemChk MemChkLib)