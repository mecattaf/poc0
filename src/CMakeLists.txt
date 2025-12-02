# Qt standard project setup
qt_standard_project_setup(REQUIRES 6.10)

# Create executable
qt_add_executable(webcompositor
    main.cpp
    compositor.h
    compositor.cpp
)

# Add QML module
qt_add_qml_module(webcompositor
    URI WebCompositor
    VERSION 1.0
    QML_FILES
        ../qml/main.qml
    RESOURCES
        ../html/test.html
)

# Link Qt libraries
target_link_libraries(webcompositor
    PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    Qt6::Quick
    Qt6::WebEngineQuick
    Qt6::WebChannel
)

# Add WebEngine compile definition
target_compile_definitions(webcompositor PRIVATE
    QT_WEBENGINE_ENABLED
)

# Link waylib and qwlroots (submodule builds)
if(TARGET WaylibSharedServer)
    target_link_libraries(webcompositor PRIVATE WaylibSharedServer)
    message(STATUS "Linking against WaylibSharedServer")
else()
    message(FATAL_ERROR "WaylibSharedServer target not found!")
endif()

if(TARGET qwlroots)
    target_link_libraries(webcompositor PRIVATE qwlroots)
    message(STATUS "Linking against qwlroots")
else()
    message(FATAL_ERROR "qwlroots target not found!")
endif()

# Explicitly add include directories (required for submodule builds)
# CRITICAL FIX: qwlroots is a sibling of waylib, not inside it!
# The structure is: external/waylib-shared/{waylib/, qwlroots/}
target_include_directories(webcompositor PRIVATE
    # Waylib server headers
    ${CMAKE_SOURCE_DIR}/external/waylib-shared/waylib/src/server
    ${CMAKE_SOURCE_DIR}/external/waylib-shared/waylib/src/server/kernel
    ${CMAKE_SOURCE_DIR}/external/waylib-shared/waylib/src/server/qtquick
    ${CMAKE_SOURCE_DIR}/external/waylib-shared/waylib/src/server/protocols
    ${CMAKE_SOURCE_DIR}/external/waylib-shared/waylib/src/server/utils

    # qwlroots headers - NOTE: qwlroots is SIBLING of waylib, not inside it!
    ${CMAKE_SOURCE_DIR}/external/waylib-shared/qwlroots/src
    ${CMAKE_SOURCE_DIR}/external/waylib-shared/qwlroots/src/types
    ${CMAKE_SOURCE_DIR}/external/waylib-shared/qwlroots/src/render
    ${CMAKE_SOURCE_DIR}/external/waylib-shared/qwlroots/src/util
    ${CMAKE_SOURCE_DIR}/external/waylib-shared/qwlroots/src/interfaces

    # Generated headers from build directory
    ${CMAKE_BINARY_DIR}/external/waylib-shared/waylib/src/server
    ${CMAKE_BINARY_DIR}/external/waylib-shared/waylib/qwlroots
)

# Find and link wlroots and wayland-server via pkg-config
find_package(PkgConfig REQUIRED)
pkg_check_modules(WLROOTS IMPORTED_TARGET wlroots-0.19)
pkg_check_modules(WAYLAND_SERVER IMPORTED_TARGET wayland-server)

if(WLROOTS_FOUND)
    target_link_libraries(webcompositor PRIVATE PkgConfig::WLROOTS)
    message(STATUS "Found wlroots: ${WLROOTS_VERSION}")
endif()

if(WAYLAND_SERVER_FOUND)
    target_link_libraries(webcompositor PRIVATE PkgConfig::WAYLAND_SERVER)
    message(STATUS "Found wayland-server: ${WAYLAND_SERVER_VERSION}")
endif()
