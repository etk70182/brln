set( PROJECT_ROOT_DIR ${PROJECT_ROOT_DIR} PARENT_SCOPE )
set( PROJECT_INCLUDE_DIR ${PROJECT_INCLUDE_DIR} PARENT_SCOPE )


find_package(Qt5 COMPONENTS Widgets REQUIRED)

# main code
add_executable(pd_sample
    mainwindow.ui
    mainwindow.cpp
    main.cpp
)

target_link_libraries(pd_sample PUBLIC libpw Qt5::Widgets)

target_include_directories(pd_sample PUBLIC ${PROJECT_INCLUDE_DIR}/c++11)

add_custom_command(TARGET pd_sample POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   ${CMAKE_SOURCE_DIR}/pd/ $<TARGET_FILE_DIR:pd_sample>/pd/)
