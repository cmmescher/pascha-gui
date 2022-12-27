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

# Build library
add_subdirectory(src)

# Test only in main project
if((CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME OR PASCHA_GUI_BUILD_TESTING)
    AND BUILD_TESTING)
  add_subdirectory(test)
endif()

option(USE_SYSTEM_WX "Use system wxWidgets" ON)
add_subdirectory(extern)
add_subdirectory(app)

