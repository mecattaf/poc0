cmake_minimum_required(VERSION 3.16)

project(web-shell VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick WebEngineQuick WebChannel)

qt_standard_project_setup()

qt_add_executable(web-shell
    src/main.cpp
    src/CoreService.cpp
    src/CoreService.h
)

qt_add_qml_module(web-shell
    URI WebShell
    VERSION 1.0
    QML_FILES resources/qml/main.qml
)

qt_add_resources(web-shell "web_resources"
    PREFIX "/"
    FILES
        resources/web/index.html
        resources/web/webshell.js
)

target_link_libraries(web-shell
    PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    Qt6::Quick
    Qt6::WebEngineQuick
    Qt6::WebChannel
)
