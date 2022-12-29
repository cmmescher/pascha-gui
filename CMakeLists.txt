cmake_minimum_required(VERSION 3.12...3.25)

project(
  pascha-gui
  VERSION 0.1
  LANGUAGES CXX
)

# Only in main project
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)

  set(CMAKE_CXX_EXTENSIONS OFF)
  set(CMAKE_CXX_STANDARD 20)

  # For folders in IDEs
  set_property(GLOBAL PROPERTY USE_FOLDERS ON)

  # Testing
  option(BUILD_TESTING "Build tests" OFF)
  include(CTest)
endif()

include(FetchContent)

# Statically build for Windows
if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
  set(BUILD_FOR_WINDOWS TRUE)
endif()
option(STATIC_BUILD "Build statically" ${BUILD_FOR_WINDOWS})

if (STATIC_BUILD AND BUILD_FOR_WINDOWS)
  set(CMAKE_EXE_LINKER_FLAGS "-static")
  set(CMAKE_FIND_LIBRARY_SUFFIXES ".a" CONFIG)
  set(CMAKE_BUILD_SHARED_LIBS OFF)
endif()

# Build library
add_subdirectory(src)

# Test only in main project
if((CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME OR PASCHA_GUI_BUILD_TESTING)
    AND BUILD_TESTING)
  add_subdirectory(test)
endif()

option(USE_SYSTEM_WX "Use system wxWidgets" ON)
if(USE_SYSTEM_WX)
  find_package(wxWidgets QUIET)
  if(NOT wxWidgets_FOUND)
    set(USE_SYSTEM_WX OFF)
  endif()
endif()

option(USE_SYSTEM_FMT "Use system fmt" ON)
if(USE_SYSTEM_FMT)
  find_package(fmt QUIET)
  if(NOT fmt_FOUND)
    set(USE_SYSTEM_FMT OFF)
  endif()
endif()

add_subdirectory(extern)
add_subdirectory(app)

install(TARGETS pascha-gui)
