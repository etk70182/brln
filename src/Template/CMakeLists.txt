set( PROJECT_ROOT_DIR ${PROJECT_ROOT_DIR} PARENT_SCOPE )
set( PROJECT_INCLUDE_DIR ${PROJECT_INCLUDE_DIR} PARENT_SCOPE )
include(${PROJECT_ROOT_DIR}/fetch_git_repo.cmake)

fetch_git_repo(
libpd
${CMAKE_BINARY_DIR}/_deps
https://github.com/libpd/libpd.git
""
)

# adds the targers: gtest, gtest_main, gmock, gmock_main
add_subdirectory(
${libpd_SOURCE_DIR}
${libpd_BINARY_DIR}
)

add_library(sum_integers sum_integers.cpp)

target_include_directories(sum_integers PUBLIC ${PROJECT_INCLUDE_DIR}/Template
											   ${libpd_SOURCE_DIR}/cpp
											   ${libpd_SOURCE_DIR}/pure-data/src
											   ${libpd_SOURCE_DIR}/pure-data/extra
											   ${libpd_SOURCE_DIR}/libpd_wrapper
											   ${libpd_SOURCE_DIR}/libpd_wrapper/util)

target_compile_definitions(sum_integers PUBLIC LIBPD_USE_STD_MUTEX)

target_link_libraries(sum_integers
PUBLIC
  libpd
)
