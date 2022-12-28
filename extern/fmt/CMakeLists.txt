if(USE_SYSTEM_FMT)
  find_package(fmt REQUIRED)
else()
  # Download fmt

  # fmt version
  set(FMT_VERSION 9.1.0)

  FetchContent_Declare(
    fmt
    GIT_REPOSITORY https://github.com/fmtlib/fmt.git
    GIT_TAG ${FMT_VERSION}
    GIT_SHALLOW TRUE
  )

  FetchContent_MakeAvailable(fmt)
endif()
