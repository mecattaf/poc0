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
)

# Link Qt libraries
target_link_libraries(webcompositor
    PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    Qt6::Quick
)

# Link waylib and qwlroots if available
if(TARGET Waylib::SharedServer)
    target_link_libraries(webcompositor
        PRIVATE
        Waylib::SharedServer
    )
    message(STATUS "Linking against Waylib::SharedServer")
endif()

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
