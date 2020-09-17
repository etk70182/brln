set(CPACK_PACKAGE_NAME "${PROJECT_NAME}")
set(CPACK_PACKAGE_VENDOR "brln")
set(CPACK_PACKAGE_DESCRIPTION_FILE "${PROJECT_SOURCE_DIR}/README.md")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "brln: a free software synthesizer")
set(CPACK_RESOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/LICENSE")

set(CPACK_PACKAGING_INSTALL_PREFIX "/opt/${PROJECT_NAME}")

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_SOURCE_IGNORE_FILES 
	"${PROJECT_BINARY_DIR};/.git/;.gitignore;/.github/;CMakeLists.txt.user;.cproject;.project"
)
set(CPACK_SOURCE_GENERATOR "ZIP;TGZ")
set(CPACK_GENERATOR "ZIP;TGZ")

if(UNIX)
  if(CMAKE_SYSTEM_NAME MATCHES Linux)
    list(APPEND CPACK_GENERATOR "DEB")
    set(CPACK_DEBIAN_PACKAGE_MAINTAINER "etk70182")
    set(CPACK_DEBIAN_PACKAGE_SECTION "devel")
    set(CPACK_DEBIAN_PACKAGE_DEPENDS "libjack-dev libasound2-dev")
  endif()
endif()

if(WIN32 OR MINGW)
  list(APPEND CPACK_GENERATOR "NSIS")
  set(CPACK_NSIS_PACKAGE_NAME "brln")
  set(CPACK_NSIS_CONTACT "etk70182")
  set(CPACK_NSIS_ENABLE_UNINSTALL_BEFORE_INSTALL ON)
endif()

#if(APPLE)
#  list(APPEND CPACK_GENERATOR "Bundle")
#  set(CPACK_BUNDLE_NAME "brln")
#  configure_file(${PROJECT_SOURCE_DIR}/cmake/Info.plist.in ${CMAKE_CURRENT_BINARY_DIR}/../Info.plist @ONLY)
#  set(CPACK_BUNDLE_PLIST ${CMAKE_CURRENT_BINARY_DIR}/../Info.plist)
#  set(CPACK_BUNDLE_ICON ${PROJECT_SOURCE_DIR}/cmake/brln.icns)
#endif()

message(STATUS "CPack generators: ${CPACK_GENERATOR}")

include(CPack)
