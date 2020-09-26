include(fetch_git_repo)

fetch_git_repo(
googletest
${CMAKE_BINARY_DIR}/_deps
https://github.com/google/googletest.git
release-1.8.0
)

# Prevent GoogleTest from overriding our compiler/linker options
# when building with Visual Studio
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
# Prevent GoogleTest from using PThreads
set(gtest_disable_pthreads ON CACHE BOOL "" FORCE)

# adds the targers: gtest, gtest_main, gmock, gmock_main
add_subdirectory(
${googletest_SOURCE_DIR}
${googletest_BINARY_DIR}
)

# Silence std::tr1 warning on MSVC
if(MSVC)
foreach(_tgt gtest gtest_main gmock gmock_main)
  target_compile_definitions(${_tgt}
    PRIVATE
      "_SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING"
    )
endforeach()
endif()


message(STATUS "Unit Tests set to:")
if(CONTAINER_ENV_DEFINITIONS)
message(STATUS "Container environment")
add_definitions(-DCONTAINER_ENV)
else()
message(STATUS "Local environment")
endif()

add_executable(unit_tests "")

target_sources(unit_tests
PRIVATE
  soundengine_test.cpp
)

target_link_libraries(unit_tests
PRIVATE
  libpw
  gtest_main
)

add_test(
NAME unit_tests
COMMAND $<TARGET_FILE:unit_tests>
)
set_tests_properties(unit_tests PROPERTIES
        WORKING_DIRECTORY $<TARGET_FILE_DIR:unit_tests>)

include(CodeCoverage)

string(TOLOWER "${CMAKE_BUILD_TYPE}" cmake_build_type_tolower)
if (cmake_build_type_tolower STREQUAL "coverage")


    # Check prereqs
    FIND_PROGRAM( GCOV_PATH gcov )
    FIND_PROGRAM( LCOV_PATH lcov )
    FIND_PROGRAM( GENHTML_PATH genhtml )
    FIND_PROGRAM( GCOVR_PATH gcovr PATHS ${CMAKE_SOURCE_DIR}/test)

    IF(NOT GCOV_PATH)
        MESSAGE(FATAL_ERROR "gcov not found! Aborting...")
    ENDIF() # NOT GCOV_PATH

    IF(NOT CMAKE_COMPILER_IS_GNUCXX)
        IF(NOT "${CMAKE_CXX_COMPILER_ID}" MATCHES ".*Clang")
            MESSAGE(FATAL_ERROR "Compiler is not GNU gcc or Clang! Aborting...")
        ENDIF()
    ENDIF() # NOT CMAKE_COMPILER_IS_GNUCXX

    SET(CMAKE_CXX_FLAGS_COVERAGE
        "-g -O0 -fprofile-arcs -ftest-coverage"
        CACHE STRING "Flags used by the C++ compiler during coverage builds."
        FORCE )
    SET(CMAKE_C_FLAGS_COVERAGE
        "-g -O0 -fprofile-arcs -ftest-coverage"
        CACHE STRING "Flags used by the C compiler during coverage builds."
        FORCE )
    SET(CMAKE_EXE_LINKER_FLAGS_COVERAGE
        ""
        CACHE STRING "Flags used for linking binaries during coverage builds."
        FORCE )
    SET(CMAKE_SHARED_LINKER_FLAGS_COVERAGE
        ""
        CACHE STRING "Flags used by the shared libraries linker during coverage builds."
        FORCE )
    MARK_AS_ADVANCED(
        CMAKE_CXX_FLAGS_COVERAGE
        CMAKE_C_FLAGS_COVERAGE
        CMAKE_EXE_LINKER_FLAGS_COVERAGE
        CMAKE_SHARED_LINKER_FLAGS_COVERAGE )


    # If unwanted files are included in the coverage reports, you can 
    # adjust the exclude patterns on line 83. 
    SETUP_TARGET_FOR_COVERAGE(
                            coverage            # Name for custom target.
                            unit_tests          # Name of the test driver executable that runs the tests.
                                                # NOTE! This should always have a ZERO as exit code
                                                # otherwise the coverage generation will not complete.
                            coverage            # Name of output directory.
                            )
else() 
    add_custom_target(coverage 
        COMMAND echo "${Red}Code coverage only available in coverage builds." 
        COMMAND echo "${Green}Make a new build directory and rerun cmake with -DCMAKE_BUILD_TYPE=Coverage to enable this target.${ColorReset}" 
    )
endif()
