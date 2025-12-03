import QtQuick
import QtQuick.Controls
import QtWebEngine
import QtWebChannel

ApplicationWindow {
    width: 1024
    height: 768
    visible: true
    title: qsTr("Web Shell Phase 0")

    WebEngineView {
        id: webView
        anchors.fill: parent
        url: "qrc:/resources/web/index.html"
        webChannel: webChannel
    }
}
