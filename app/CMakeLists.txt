set( PROJECT_ROOT_DIR ${PROJECT_ROOT_DIR} PARENT_SCOPE )
set( PROJECT_INCLUDE_DIR ${PROJECT_INCLUDE_DIR} PARENT_SCOPE )

# main code
add_executable(sum_up main.cpp)
target_link_libraries(sum_up sum_integers)
