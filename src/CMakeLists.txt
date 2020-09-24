set( PROJECT_ROOT_DIR ${PROJECT_ROOT_DIR} PARENT_SCOPE )
set( PROJECT_INCLUDE_DIR ${PROJECT_INCLUDE_DIR} PARENT_SCOPE )

add_subdirectory(libpw)
message(STATUS "libpd lib is set to ${LIBPD_LIB}")
add_subdirectory(app)
add_subdirectory(Template)
