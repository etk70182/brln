# (1) Build a library with my application sources
set(APP_LIB_SOURCE Template/Template.cpp)

add_library(${APP_LIB_NAME} STATIC ${APP_LIB_SOURCE})

# (2) Add main(..) to the application library to have something we can run
add_executable(${APP_NAME} main.cpp)
target_compile_features(${APP_NAME} PRIVATE cxx_lambda_init_captures)
target_link_libraries(${APP_NAME} ${APP_LIB_NAME})
