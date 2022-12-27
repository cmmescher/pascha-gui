find_package(fmt QUIET)

if(fmt_FOUND)
  add_library(fmt INTERFACE)
  target_link_libraries(fmt INTERFACE fmt::fmt)
  add_library(pascha::fmt ALIAS fmt)
else()
  # Download fmt from github

  # fmt version
  set(FMT_VERSION 9.1.0)

  set(FMT_SRC_ARCHIVE "${CMAKE_CURRENT_SOURCE_DIR}/fmt-${FMT_VERSION}.zip")
  set(FMT_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/fmt-${FMT_VERSION}")
  set(FMT_BUILD_DIR "${CMAKE_CURRENT_BINARY_DIR}/fmt-${FMT_VERSION}-build")

  # Download from github
  if(NOT EXISTS ${FMT_SRC_ARCHIVE})
    message(STATUS "Downloading fmt ${FMT_VERSION} files. Please wait...")
    file(DOWNLOAD
      "https://github.com/fmtlib/fmt/releases/download/${FMT_VERSION}/fmt-${FMT_VERSION}.zip"
      ${FMT_SRC_ARCHIVE}
      SHOW_PROGRESS
    )
  endif()

  # Extracting files
  if(NOT EXISTS ${FMT_SRC_DIR})
    execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ${FMT_SRC_DIR})
    message(STATUS "Extracting fmt ${FMT_VERSION} files. Please wait...")
    execute_process(
      COMMAND ${CMAKE_COMMAND} -E unzip ${FMT_SRC_ARCHIVE}
      WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    )
  endif()

  add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/fmt-${FMT_VERSION}" EXCLUDE_FROM_ALL)

  add_library(fmt INTERFACE)
  target_link_libraries(fmt INTERFACE fmt::fmt)
  add_library(pascha::fmt ALIAS fmt)
endif()
