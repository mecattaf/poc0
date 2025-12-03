# Part C: The Debate & Resolution

## The Debate
**Proposition:** "We should reimplement 'what Quickshell does for Qt' but for QtWebEngine."

**Side A: The "Purist" Web Approach**
*   *Argument:* Just launch a browser. Use standard Web APIs. If the Web API doesn't exist (e.g., Battery API is deprecated), too bad. Keep it simple.
*   *Counter:* A desktop shell *needs* system access. You can't build a taskbar without knowing what windows are open. You can't build a system tray without DBus. A standard browser is a sandbox; a shell must be a fortress commander.

**Side B: The "Integration" Approach (Our Path)**
*   *Argument:* Build a specialized runtime. We are not building a browser; we are building a **Desktop Environment Runtime** that happens to use HTML/CSS for rendering.
*   *Implication:* We must manually implement every single system API in C++ and expose it. This is a lot of work. `Quickshell` has already done this for QML.

## The Resolution
**YES, we reimplement it.**

We are effectively building **"Electron, but optimized for Shells."**
*   Electron is general-purpose. It's heavy and doesn't have "Wayland Window Management" APIs out of the box.
*   `WebShell` is specific. It includes pre-baked C++ modules for:
    *   `wlr-layer-shell` (to stick to the background/panel).
    *   `wlr-foreign-toplevel` (to list windows).
    *   `UPower`, `NetworkManager`, `Pipewire`.

## The "Wrapper" Reality
We are writing a **QtQuick Wrapper** around `QtWebEngine`.
*   **Why QtQuick?** Because `QtWebEngine` *is* a QtQuick component (`WebEngineView`).
*   **Why Wrap?** To inject the `QtWebChannel`.

## The Architecture
1.  **The Binary (`web-shell`):**
    *   A C++ Qt application.
    *   Loads a hidden `main.qml`.
    *   Instantiates `WebEngineView`.
    *   **The "Secret Sauce":** It instantiates a `ShellObjectManager` (C++) which collects all the Services (Battery, Network, etc.).
    *   It registers this Manager with `QtWebChannel`.

2.  **The SDK (`webshell.js`):**
    *   A small JS library we ship.
    *   It connects to the channel.
    *   It exposes the global `WebShell` object.

3.  **The User Code (`index.html`):**
    *   User writes: `WebShell.System.reboot()`.
    *   No C++ knowledge required.

## Conclusion
We are building a **Domain-Specific Runtime**.
*   **Input:** HTML/JS + `WebShell` API.
*   **Output:** A native Wayland Desktop Shell.
*   **Mechanism:** C++ Backend (Services) <-> QtWebChannel <-> JS Frontend.
