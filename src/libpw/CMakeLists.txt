set( PROJECT_ROOT_DIR ${PROJECT_ROOT_DIR} PARENT_SCOPE )
set( PROJECT_INCLUDE_DIR ${PROJECT_INCLUDE_DIR} PARENT_SCOPE )
include(fetch_git_repo)

fetch_git_repo(
libpd
${CMAKE_BINARY_DIR}/_deps
https://github.com/etk70182/libpd.git
"23ef53c280259921cd8396205e8191be647ab1c2"
)

# adds the targers: libpd_static, libpd
add_subdirectory(
${libpd_SOURCE_DIR}
${libpd_BINARY_DIR}
)

add_library(libpw PdObject.cpp RtAudio.cpp)

target_include_directories(libpw PUBLIC ${PROJECT_INCLUDE_DIR}/libpw
											   ${libpd_SOURCE_DIR}/cpp
											   ${libpd_SOURCE_DIR}/pure-data/src
											   ${libpd_SOURCE_DIR}/pure-data/extra
											   ${libpd_SOURCE_DIR}/libpd_wrapper
											   ${libpd_SOURCE_DIR}/libpd_wrapper/util)

set(LIBPW_COMPILE_FLAGS "")
set(LIBPW_AUDIO_API "")

if(WIN32)
list(APPEND LIBPW_COMPILE_FLAGS __WINDOWS_DS__)
list(APPEND LIBPW_AUDIO_API ole32 oleaut32 dsound winmm)
elseif((${CMAKE_SYSTEM_NAME} MATCHES "Darwin"))
list(APPEND LIBPW_COMPILE_FLAGS __MACOSX_CORE__ HAVE_UNISTD_H)
list(APPEND LIBPW_AUDIO_API "-framework Foundation" "-framework CoreAudio")
else()
list(APPEND LIBPW_COMPILE_FLAGS __UNIX_JACK__ __LINUX_ALSA__)
list(APPEND LIBPW_AUDIO_API jack asound pthread)
endif()

target_compile_definitions(libpw
PUBLIC
  LIBPD_USE_STD_MUTEX
  ${LIBPW_COMPILE_FLAGS}
)

if(MSVC)
target_link_libraries(libpw
STATIC
  libpd-multi-static
)
target_link_libraries(libpw
PUBLIC
  ${LIBPW_AUDIO_API}
)
else()
target_link_libraries(libpw
PUBLIC
  libpd
  ${LIBPW_AUDIO_API}
)
endif()
