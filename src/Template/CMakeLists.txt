set( PROJECT_ROOT_DIR ${PROJECT_ROOT_DIR} PARENT_SCOPE )
set( PROJECT_INCLUDE_DIR ${PROJECT_INCLUDE_DIR} PARENT_SCOPE )
include(${PROJECT_ROOT_DIR}/fetch_git_repo.cmake)

fetch_git_repo(
libpd
${CMAKE_BINARY_DIR}/_deps
https://github.com/etk70182/libpd.git
"225553d2d5ca89db56e6a55b1011fb6861188ed3"
)

if (MSVC)
    set(CMAKE_THREAD_LIBS_INIT ${PROJECT_ROOT_DIR}/libs/x64/pthreadVC2.lib CACHE STRING "Path to pthreads library")
    set(PTHREADS_INCLUDE_DIR ${PROJECT_ROOT_DIR}/include/pthreads_win32/ CACHE STRING "Path to the pthreads library header files")
endif ()

# adds the targers: libpd_static, libpd
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
