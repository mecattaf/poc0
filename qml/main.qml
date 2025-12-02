import QtQuick
import QtWebEngine

Item {
    id: root
    anchors.fill: parent

    // WebEngine view for rendering web content
    WebEngineView {
        id: webView
        anchors.fill: parent
        url: "qrc:/qt/qml/WebCompositor/html/test.html"

        Component.onCompleted: {
            console.log("WebEngineView created")
        }

        onLoadingChanged: function(loadRequest) {
            if (loadRequest.status === WebEngineView.LoadSucceededStatus) {
                console.log("WebEngine page loaded successfully")
            } else if (loadRequest.status === WebEngineView.LoadFailedStatus) {
                console.error("WebEngine page load failed:", loadRequest.errorString)
            }
        }

        onRenderProcessTerminated: function(terminationStatus, exitCode) {
            console.error("WebEngine render process terminated:", terminationStatus, exitCode)
        }
    }
}
