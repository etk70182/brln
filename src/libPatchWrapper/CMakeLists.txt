set( PROJECT_ROOT_DIR ${PROJECT_ROOT_DIR} PARENT_SCOPE )
set( PROJECT_INCLUDE_DIR ${PROJECT_INCLUDE_DIR} PARENT_SCOPE )
include(fetch_git_repo)

fetch_git_repo(
libpd
${CMAKE_BINARY_DIR}/_deps
https://github.com/etk70182/libpd.git
"061a624785196f3f40a57cc4ad4b76eb02c14656"
)

# adds the targers: libpd_static, libpd
add_subdirectory(
${libpd_SOURCE_DIR}
${libpd_BINARY_DIR}
)

add_library(libPatchWrapper PdObject.cpp RtAudio.cpp)

target_include_directories(libPatchWrapper PUBLIC ${PROJECT_INCLUDE_DIR}/libPatchWrapper
											   ${libpd_SOURCE_DIR}/cpp
											   ${libpd_SOURCE_DIR}/pure-data/src
											   ${libpd_SOURCE_DIR}/pure-data/extra
											   ${libpd_SOURCE_DIR}/libpd_wrapper
											   ${libpd_SOURCE_DIR}/libpd_wrapper/util)

set(LIBPATCHWRAPPER_COMPILE_FLAGS "")
set(LIBPATCHWRAPPER_AUDIO_API "")

if(WIN32)
list(APPEND LIBPATCHWRAPPER_COMPILE_FLAGS __WINDOWS_DS__)
list(APPEND LIBPATCHWRAPPER_AUDIO_API ole32 oleaut32 dsound winmm)
elseif((${CMAKE_SYSTEM_NAME} MATCHES "Darwin"))
list(APPEND LIBPATCHWRAPPER_COMPILE_FLAGS __MACOSX_CORE__ HAVE_UNISTD_H)
list(APPEND LIBPATCHWRAPPER_AUDIO_API "-framework Foundation" "-framework CoreAudio")
else()
list(APPEND LIBPATCHWRAPPER_COMPILE_FLAGS __UNIX_JACK__ __LINUX_ALSA__)
list(APPEND LIBPATCHWRAPPER_AUDIO_API jack asound pthread)
endif()

target_compile_definitions(libPatchWrapper
PUBLIC
  LIBPD_USE_STD_MUTEX
  ${LIBPATCHWRAPPER_COMPILE_FLAGS}
)

target_link_libraries(libPatchWrapper
PUBLIC
  libpd
  ${LIBPATCHWRAPPER_AUDIO_API}
)

