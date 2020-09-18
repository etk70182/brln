# set minimum cmake version
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

# project name and language
project(brln 
	LANGUAGES CXX C
	VERSION 0.1.0
)

# require C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Qt
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)

set(PROJECT_ROOT_DIR ${CMAKE_CURRENT_LIST_DIR})
set(PROJECT_INCLUDE_DIR ${PROJECT_ROOT_DIR}/include)

# CPack for Source packaging
message(STATUS "CMake installation path ${CMAKE_INSTALL_PREFIX}")

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()
message(STATUS "Build type set to ${CMAKE_BUILD_TYPE}")

include(GNUInstallDirs)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})

# Offer the user the choice of overriding the installation directories
set(INSTALL_LIBDIR ${CMAKE_INSTALL_LIBDIR} CACHE PATH "Installation directory for libraries")
set(INSTALL_BINDIR ${CMAKE_INSTALL_BINDIR} CACHE PATH "Installation directory for executables")
set(INSTALL_INCLUDEDIR ${CMAKE_INSTALL_INCLUDEDIR} CACHE PATH "Installation directory for header files")
if(WIN32 AND NOT CYGWIN)
  set(DEF_INSTALL_CMAKEDIR CMake)
else()
  set(DEF_INSTALL_CMAKEDIR share/cmake/${PROJECT_NAME})
endif()
set(INSTALL_CMAKEDIR ${DEF_INSTALL_CMAKEDIR} CACHE PATH "Installation directory for CMake files")

# Report to user
foreach(p LIB BIN INCLUDE CMAKE)
  file(TO_NATIVE_PATH ${CMAKE_INSTALL_PREFIX}/${INSTALL_${p}DIR} _path )
  message(STATUS "Installing ${p} components to ${_path}")
  unset(_path)
endforeach()

# For macOS, the output directories form the app bundle; for all other
# platforms, the output paths mirror the installation paths
if(APPLE AND MACOS_BUNDLE_FORMAT)
    set(CONTENTS_DIRECTORY "${CMAKE_BINARY_DIR}/brln.app/Contents")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CONTENTS_DIRECTORY}/MacOS")
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CONTENTS_DIRECTORY}/Frameworks")
    set(PLUGIN_OUTPUT_DIRECTORY "${CONTENTS_DIRECTORY}/PlugIns/brln")
endif()

# configure version
configure_file(${PROJECT_SOURCE_DIR}/cmake/version.h.in ${PROJECT_INCLUDE_DIR}/app/version.h @ONLY)

# example library
add_subdirectory(src)


#install(TARGET libpd DESTINATION ${INSTALL_LIBDIR})

# we will use the network to fetch Google Test sources
# make it possible to disable unit tests when not on network
option(ENABLE_UNIT_TESTS "Enable unit tests" ON)
message(STATUS "Enable testing: ${ENABLE_UNIT_TESTS}")

if(ENABLE_UNIT_TESTS)
  enable_testing()
  add_subdirectory(test)
endif()

include(CMakeCPack)

#configure package scripts
configure_file(${PROJECT_SOURCE_DIR}/cmake/package-linux-appimage.sh.in ${PROJECT_SOURCE_DIR}/scripts/package-linux-appimage.sh @ONLY)
configure_file(${PROJECT_SOURCE_DIR}/cmake/package-macosx.sh.in ${PROJECT_SOURCE_DIR}/scripts/package-macosx.sh @ONLY)
configure_file(${PROJECT_SOURCE_DIR}/cmake/package-windows.bat.in ${PROJECT_SOURCE_DIR}/scripts/package-windows.bat @ONLY)
