# set minimum cmake version
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

# project name and language
project(brln LANGUAGES CXX C)

# require C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)

set(PROJECT_ROOT_DIR ${CMAKE_CURRENT_LIST_DIR})
set(PROJECT_INCLUDE_DIR ${PROJECT_ROOT_DIR}/include)

# main application
add_subdirectory(app)

# example library
add_subdirectory(src)

# we will use the network to fetch Google Test sources
# make it possible to disable unit tests when not on network
option(ENABLE_UNIT_TESTS "Enable unit tests" ON)
message(STATUS "Enable testing: ${ENABLE_UNIT_TESTS}")

if(ENABLE_UNIT_TESTS)
  enable_testing()
  #include(CTest)
  add_subdirectory(test)
endif()
