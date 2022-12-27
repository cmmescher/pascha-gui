file(GLOB HEADER_LIST "${pascha-gtk_SOURCE_DIR}/src/*.hpp")

add_library(
  pascha-lib
  calculation_method_decorator.cpp
  calculation_methods.cpp
  calendar_conversion.cpp
  gui_controller.cpp
  output_calendars.cpp
  output_options.cpp
  pascha_calculator_model.cpp
  target_date.cpp
  ${HEADER_LIST}
)

target_include_directories(pascha-lib PUBLIC ../include)

target_compile_features(pascha-lib PUBLIC cxx_std_20)

# IDE header organization
source_group(
  TREE "${PROJECT_SOURCE_DIR}/include"
  PREFIX "Header Files"
  FILES ${HEADER_LIST})
