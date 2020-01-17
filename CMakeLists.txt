# (1) CMake definitions, compiler flags and useful variables
cmake_minimum_required(VERSION 3.7)
project(brln)

SET(CMAKE_C_COMPILER /usr/bin/gcc-7)
SET(CMAKE_CXX_COMPILER /usr/bin/g++-7)

add_compile_options(-Wall -Werror -Wpedantic)

set(APP_NAME brln)
set(APP_LIB_NAME Template)

# (2) Include application build instructions
add_subdirectory(src)

# (3) include tests build instructions   
option(COMPILE_TESTS "Compile the tests" ON)
if(COMPILE_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif(COMPILE_TESTS)
