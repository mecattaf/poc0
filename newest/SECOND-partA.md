# Part A: Initialization Strategy

## The Question
Should we use `QtWebEngine`, raw Chromium (CEF), or a hybrid approach? How do we initialize the runtime?

## Analysis

### Option 1: Raw Chromium / CEF
*   **Pros:** Minimal dependency footprint (no Qt), potentially lighter if highly optimized.
*   **Cons:** Zero "free" IPC. You have to invent your own message passing (JSON-RPC over stdin/stdout) to talk between your C++ backend and the JS frontend. No declarative binding engine.
*   **Verdict:** Too much boilerplate. We want to focus on the *Shell API*, not writing a browser harness.

### Option 2: Pure QtWebEngine (C++ Widgets)
*   **Pros:** Standard Qt.
*   **Cons:** The "Widgets" module is aging. Less flexible for hardware acceleration integration than Quick.

### Option 3: QtWebEngine via QtQuick (The "Quickshell" Path)
*   **Pros:**
    *   **Hardware Acceleration:** `QtWebEngineQuick` renders directly into the Qt Quick scene graph, which is optimized for the GPU.
    *   **Compositor Integration:** Since our Compositor (`webcompositor`) is also QtQuick/Waylib based, sharing context or code patterns is easier.
    *   **The "Wrapper" Pattern:** This matches the `dankmaterialshell` pattern. We create a minimal QML "container" that hosts the `WebEngineView`.

## The Decision: QtWebEngineQuick Wrapper
We will build a **Runtime Binary** (`web-shell`) that is technically a QtQuick application.

**The "Hidden" QML:**
The user *never sees* QML. We ship a hardcoded `main.qml` inside the binary resources that looks like this:
```qml
ApplicationWindow {
    WebEngineView {
        anchors.fill: parent
        url: "file:///home/user/.config/webshell/index.html"
        webChannel: nativeChannel // Injected C++ Backend
    }
}
```

**Why this wins:**
1.  **It's a Runtime:** Just like `quickshell` is a binary you run that loads user scripts, `web-shell` is a binary that loads user HTML.
2.  **Free Bridge:** `QtWebChannel` works out-of-the-box here.
3.  **Future Proof:** If we ever need a native "Overlay" (e.g., a high-performance video player or a specific Wayland surface that HTML can't handle), we can layer it in the QML parent, while keeping the user's logic in HTML.
