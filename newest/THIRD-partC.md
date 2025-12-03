# Part C: Quickshell - Merge or Diverge?

## The Resolution: Diverge Implementation, Merge Patterns

### 1. Why Diverge?
We cannot "merge" into Quickshell because **Quickshell is a QML Runtime**.
*   Quickshell's core loop is designed to load `.qml` files and instantiate `QtQuick` items.
*   WebShell's core loop is designed to load `.html` files and instantiate `QtWebEngine`.
*   They are **Siblings**. They share the same father (Qt6) but speak different languages (QML vs HTML).

### 2. The Pattern (What we steal)
We should treat Quickshell as our **Reference Implementation**.
*   **API Structure:** If Quickshell has `Quickshell.Services.Pipewire`, we should have `WebShell.Services.Pipewire`.
*   **C++ Logic:** We can literally copy-paste the C++ logic from Quickshell's backend (e.g., how it talks to Pipewire) and just change the "Exposure Layer" from `Q_PROPERTY` (for QML) to `QtWebChannel` (for JS).

### 3. IPC Integrations (Hyprland, Sway, etc.)
You mentioned Quickshell has integrations with window managers.
*   **How it works there:** Quickshell connects to the WM's IPC socket (e.g., `/tmp/hypr/...`) and parses the JSON stream.
*   **How we do it:**
    1.  We write a C++ class `HyprlandService`.
    2.  It connects to the socket using `QLocalSocket`.
    3.  It parses the JSON events.
    4.  It emits signals: `workspaceChanged`, `windowCreated`.
    5.  **The Bridge:** We register this `HyprlandService` on the WebChannel.
    6.  **The Result:** JS code can do:
        ```javascript
        Hyprland.on('workspaceChanged', (ws) => {
            console.log("Switched to", ws.name);
        });
        ```

## Conclusion
We are building the **"Web Twin"** of Quickshell.
*   **Do not merge codebases.** It will create a Frankenstein monster.
*   **Do merge concepts.** Keep the APIs identical so a user can mentally switch between Quickshell and WebShell easily.
*   **Port the Backend.** The hard work (talking to Hyprland, PulseAudio) is already done in Quickshell's C++ source. We just need to wrap it for the Web.
