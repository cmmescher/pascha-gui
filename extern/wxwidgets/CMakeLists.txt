if(USE_SYSTEM_WX)
    find_package(wxWidgets REQUIRED)

    # Meta target to easily use wxWidgets
    add_library(wx INTERFACE)

    target_include_directories(wx
        INTERFACE
            ${wxWidgets_INCLUDE_DIRS}
    )

    target_compile_definitions(wx
        INTERFACE
            ${wxWidgets_DEFINITIONS}
    )

    target_link_directories(wx
        INTERFACE
            ${wxWidgets_LIBRARY_DIRS}
    )

    target_link_libraries(wx
        INTERFACE
            ${wxWidgets_LIBRARIES}
    )

    add_library(pascha::wx ALIAS wx)
else()
  # Download wxWidgets

  # wxWidgets version
  set(WX_VERSION 3.1.4)

  FetchContent_Declare(
    wxWidgets
    GIT_REPOSITORY https://github.com/wxWidgets/wxWidgets.git
    GIT_TAG v${WX_VERSION}
    GIT_SHALLOW TRUE
  )

  # wxWidgets config
  set(wxBUILD_SHARED OFF)
  set(wxBUILD_INSTALL OFF)
  set(wxBUILD_PRECOMP OFF)
  set(wxBUILD_MONOLITHIC OFF)

  set(wxUSE_OPENGL OFF)
  set(wxUSE_WEBVIEW OFF)
  set(wxUSE_MEDIACTRL OFF)
  set(wxUSE_RIBBON OFF)
  set(wxUSE_STC OFF)
  set(wxUSE_PROPGRID OFF)

  FetchContent_GetProperties(wxWidgets)
  FetchContent_MakeAvailable(wxWidgets)

  add_library(wx INTERFACE)

  if(wxBUILD_SHARED)
      target_compile_definitions(wx
          INTERFACE
              -DWXUSINGDLL
      )
  endif()

  target_link_libraries(wx
      INTERFACE
          wxbase
          wxcore
          wxadv
          wxhtml
          wxnet
          wxqa
          wxaui
          wxrichtext
          wxxml
          wxxrc
  )

  if(wxUSE_PROPGRID)
      target_link_libraries(wx
          INTERFACE
              wxpropgrid
      )
  endif()

  if(wxUSE_STC)
      target_link_libraries(wx
          INTERFACE
              wxstc
      )
  endif()

  if(wxUSE_RIBBON)
      target_link_libraries(wx
          INTERFACE
              wxribbon
      )
  endif()

  if(wxUSE_WEBVIEW)
      target_link_libraries(wx
          INTERFACE
              wxwebview
      )
  endif()

  if(wxUSE_MEDIACTRL)
      target_link_libraries(wx
          INTERFACE
              wxmedia
      )
  endif()

  if(wxUSE_OPENGL)
      target_link_libraries(wx
          INTERFACE
              wxgl
      )
  endif()

  add_library(pascha::wx ALIAS wx)
endif()
