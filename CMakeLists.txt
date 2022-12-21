cmake_minimum_required(VERSION 3.12...3.25)

project(
  pascha-gtk
  VERSION 0.1
  LANGUAGES CXX)

# Only in main project
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)

  set(CMAKE_CXX_EXTENSIONS OFF)
  set(CMAKE_CXX_STANDARD 20)

  # For folders in IDEs
  set_property(GLOBAL PROPERTY USE_FOLDERS ON)

  # Testing
  include(CTest)
endif()

include(FetchContent)

add_subdirectory(src)

# Test only in main project
if((CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME OR PASCHA_GTK_BUILD_TESTING)
    AND BUILD_TESTING)
  add_subdirectory(test)
endif()
