set( PROJECT_ROOT_DIR ${PROJECT_ROOT_DIR} PARENT_SCOPE )
set( PROJECT_INCLUDE_DIR ${PROJECT_INCLUDE_DIR} PARENT_SCOPE )


find_package(Qt5 COMPONENTS Widgets REQUIRED)

set(APP_SOURCES main.cpp mainwindow.cpp audiothread.cpp)
qt5_wrap_cpp(APP_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/mainwindow.cpp ${PROJECT_INCLUDE_DIR}/app/mainwindow.h)
qt5_wrap_ui(UI_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/mainwindow.ui)

message(STATUS "HELLO")
message(STATUS ${UI_HEADERS})

# main code
add_executable(pd_sample ${APP_SOURCES} ${UI_HEADERS})

target_include_directories(pd_sample PUBLIC ${PROJECT_INCLUDE_DIR}/unallowedHeaders
                                                                                        ${PROJECT_INCLUDE_DIR}/app
                                                                                        ${CMAKE_CURRENT_BINARY_DIR})

target_link_libraries(pd_sample PUBLIC libpw Qt5::Widgets)

add_custom_command(TARGET pd_sample POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   ${CMAKE_SOURCE_DIR}/pd/ $<TARGET_FILE_DIR:pd_sample>/pd/)
