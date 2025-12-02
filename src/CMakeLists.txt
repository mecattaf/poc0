# Qt standard project setup
qt_standard_project_setup(REQUIRES 6.10)

# Create executable
qt_add_executable(webcompositor
    main.cpp
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

# Link waylib if available
if(TARGET Waylib::SharedServer)
    target_link_libraries(webcompositor
        PRIVATE
        Waylib::SharedServer
    )
endif()
