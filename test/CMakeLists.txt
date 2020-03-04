set( PROJECT_ROOT_DIR ${PROJECT_ROOT_DIR} PARENT_SCOPE )
include(${PROJECT_ROOT_DIR}/fetch_git_repo.cmake)

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

add_executable(cpp_test "")

target_sources(cpp_test
PRIVATE
  test.cpp
)

target_link_libraries(cpp_test
PRIVATE
  sum_integers
  gtest_main
)

add_test(
NAME google_test
COMMAND $<TARGET_FILE:cpp_test>
)
