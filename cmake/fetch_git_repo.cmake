# the following code to fetch a git repo at configure-time
# is inspired by and adapted after https://crascit.com/2015/07/25/cmake-gtest/
# defines ${_project_name}_SOURCE_DIR and ${_project_name}_BINARY_DIR
set( PROJECT_ROOT_DIR ${PROJECT_ROOT_DIR} PARENT_SCOPE )
macro(fetch_git_repo _project_name _download_root _git_url _git_tag)

  set(${_project_name}_SOURCE_DIR ${_download_root}/${_project_name}-src)
  set(${_project_name}_BINARY_DIR ${_download_root}/${_project_name}-build)

  # variables used configuring fetch_git_repo_sub.cmake
  set(FETCH_PROJECT_NAME ${_project_name})
  set(FETCH_SOURCE_DIR ${${_project_name}_SOURCE_DIR})
  set(FETCH_BINARY_DIR ${${_project_name}_BINARY_DIR})
  set(FETCH_GIT_REPOSITORY ${_git_url})
  set(FETCH_GIT_TAG ${_git_tag})

  configure_file(
    ${PROJECT_ROOT_DIR}/cmake/fetch_at_configure_step.in
    ${_download_root}/CMakeLists.txt
    @ONLY
    )

  # undefine them again
  unset(FETCH_PROJECT_NAME)
  unset(FETCH_SOURCE_DIR)
  unset(FETCH_BINARY_DIR)
  unset(FETCH_GIT_REPOSITORY)
  unset(FETCH_GIT_TAG)

  # configure sub-project
  if((${_project_name} MATCHES "libpd") AND (${CMAKE_SYSTEM_NAME} MATCHES "Windows"))
  message(STATUS "Fetching git repo for libpd.")
  execute_process(
    COMMAND
      "${CMAKE_COMMAND}" -DPD_UTILS=OFF -DPD_MULTI=ON -G "${CMAKE_GENERATOR}" .
    WORKING_DIRECTORY
      ${_download_root}
  )
  else()
  execute_process(
    COMMAND
      "${CMAKE_COMMAND}" -G "${CMAKE_GENERATOR}" .
    WORKING_DIRECTORY
      ${_download_root}
  )
  endif()

  # build sub-project which triggers ExternalProject_Add
  execute_process(
    COMMAND
      "${CMAKE_COMMAND}" --build .
    WORKING_DIRECTORY
      ${_download_root}
    )
endmacro()
