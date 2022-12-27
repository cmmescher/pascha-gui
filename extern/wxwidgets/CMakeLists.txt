if(USE_SYSTEM_WX)
    # Use standard way to find wxWidgets
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
    # Download wxWidgets from github

    # wxWidgets version
    set(WX_VERSION 3.1.4)

    set(WX_SRC_ARCHIVE "${CMAKE_CURRENT_SOURCE_DIR}/wxWidgets-${WX_VERSION}.tar.bz2")
    set(WX_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/wxWidgets-${WX_VERSION}")
    set(WX_BUILD_DIR "${CMAKE_CURRENT_BINARY_DIR}/wxWidgets-${WX_VERSION}-build")

    # Download source archive from github
    if(NOT EXISTS ${WX_SRC_ARCHIVE})
        message(STATUS "Downloading wxWidgets ${WX_VERSION} source. Please wait...")
        file(DOWNLOAD
            "https://github.com/wxWidgets/wxWidgets/releases/download/v${WX_VERSION}/wxWidgets-${WX_VERSION}.tar.bz2"
            ${WX_SRC_ARCHIVE}
            SHOW_PROGRESS
        )
    endif()

    # Extracting files
    if(NOT EXISTS ${WX_SRC_DIR})
        execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ${WX_SRC_DIR})
        message(STATUS "Extracting wxWidgets ${WX_VERSION} files. Please wait...")
        execute_process(COMMAND ${CMAKE_COMMAND} -E tar xjf ${WX_SRC_ARCHIVE}
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        )
    endif()

    # wxWidgets config
    set(wxBUILD_SHARED OFF)
    set(wxBUILD_INSTALL OFF)

    set(wxUSE_OPENGL OFF)
    set(wxUSE_WEBVIEW OFF)
    set(wxUSE_MEDIACTRL OFF)
    set(wxUSE_RIBBON OFF)
    set(wxUSE_STC OFF)
    set(wxUSE_PROPGRID OFF)

    # Add as subproject
    add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/wxWidgets-${WX_VERSION}" EXCLUDE_FROM_ALL)

    # Meta target for easy use wxWidgets
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
