# Testing library
FetchContent_Declare(
  catch
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v3.2.1)
FetchContent_MakeAvailable(catch)
# Adds Catch2::Catch2

add_executable(
  tests
  calendar_conversion_test.cpp
  calculation_methods_test.cpp
)

target_compile_features(tests PRIVATE cxx_std_20)

target_link_libraries(
  tests
  PRIVATE pascha-lib
          Catch2::Catch2WithMain)

# Register tests
add_test(NAME pascha-libtest COMMAND tests)
