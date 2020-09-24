set( PROJECT_ROOT_DIR ${PROJECT_ROOT_DIR} PARENT_SCOPE )
set( PROJECT_INCLUDE_DIR ${PROJECT_INCLUDE_DIR} PARENT_SCOPE )


find_package(Qt5 COMPONENTS Widgets REQUIRED)

set(APP_SOURCES main.cpp mainwindow.cpp audiothread.cpp)
qt5_wrap_cpp(APP_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/mainwindow.cpp ${PROJECT_INCLUDE_DIR}/app/mainwindow.h)
qt5_wrap_ui(UI_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/mainwindow.ui)
qt5_add_resources(APP_RESOURCES ${CMAKE_SOURCE_DIR}/resources/resources.qrc)
# main code
add_executable(brln ${APP_SOURCES} ${UI_HEADERS} ${APP_RESOURCES})

target_include_directories(brln PUBLIC ${PROJECT_INCLUDE_DIR}/unallowedHeaders
                                                                                        ${PROJECT_INCLUDE_DIR}/app
                                                                                        ${CMAKE_CURRENT_BINARY_DIR})

target_link_libraries(brln PUBLIC libpw ${LIBPD_LIB} Qt5::Widgets)

add_custom_command(TARGET brln POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   ${CMAKE_SOURCE_DIR}/pd/ $<TARGET_FILE_DIR:brln>/pd/)

# Prepare RPATH
if(CMAKE_SYSTEM_NAME STREQUAL "Linux" OR CMAKE_SYSTEM_NAME STREQUAL "Darwin")
	file(RELATIVE_PATH _rel ${CMAKE_INSTALL_PREFIX}/${INSTALL_BINDIR} ${CMAKE_INSTALL_PREFIX})
	if(APPLE)
	  set(_rpath "@loader_path/${_rel}")
	else()
	  set(_rpath "\$ORIGIN/${_rel}")
	endif()
	file(TO_NATIVE_PATH "${_rpath}/${INSTALL_LIBDIR}" brln_RPATH)

	set_target_properties(brln
	  PROPERTIES
		MACOSX_RPATH ON
		SKIP_BUILD_RPATH OFF
		BUILD_WITH_INSTALL_RPATH OFF
		INSTALL_RPATH "${brln_RPATH}"
		INSTALL_RPATH_USE_LINK_PATH ON
	  )
endif(CMAKE_SYSTEM_NAME STREQUAL "Linux" OR CMAKE_SYSTEM_NAME STREQUAL "Darwin")

# <<< Install and export targets >>>

install(
  TARGETS
    brln
  ARCHIVE
    DESTINATION ${INSTALL_LIBDIR}
    COMPONENT lib
  RUNTIME
    DESTINATION ${INSTALL_BINDIR}
    COMPONENT bin
  LIBRARY
    DESTINATION ${INSTALL_LIBDIR}
    COMPONENT lib
  PUBLIC_HEADER
    DESTINATION ${INSTALL_INCLUDEDIR}/brln
    COMPONENT dev
  )

install(FILES ${CMAKE_SOURCE_DIR}/pd/test.pd DESTINATION ${INSTALL_BINDIR}/pd)
file(GLOB LIBPD_TARGETS ${CMAKE_BINARY_DIR}/_deps/libpd-src/libs/libpd${CMAKE_SHARED_LIBRARY_SUFFIX})
install(FILES ${LIBPD_TARGETS} DESTINATION ${INSTALL_LIBDIR})

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    include(DeployQt)
    windeployqt(brln)
endif()

if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    include(DeployQt)
    macdeployqt(brln)
endif()
