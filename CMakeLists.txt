cmake_minimum_required(VERSION 3.4)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DSTATICLIB -std=c++11")

set(CMAKE_DIR "${CMAKE_CURRENT_LIST_DIR}/cmake" CACHE PATH "The path to the cmake directory")
list(APPEND CMAKE_MODULE_PATH ${CMAKE_DIR})
set(PAILLIER_DIR "${CMAKE_CURRENT_LIST_DIR}" CACHE PATH "Path to the root directory for paillier")

include_directories(${PAILLIER_DIR})

add_subdirectory(paillierCpp)

add_executable(testAdd testAdd.cpp)
target_link_libraries(testAdd paillier)