# Product Requirements Document (PRD): WebShell

## 1. Executive Summary
**WebShell** is a programmable Wayland desktop shell powered by standard Web Technologies (HTML/CSS/JS). It combines the rendering power and developer ecosystem of the Web with the native system access of a compiled desktop environment. It is designed to be the "Quickshell for the Web."

## 2. Core Goals
1.  **Web-First DX:** A developer should be able to build a full desktop shell using *only* HTML, CSS, and JavaScript. No C++ required for the end user.
2.  **Native Power:** The JavaScript environment must have access to low-level system APIs (Battery, Network, Bluetooth, Wayland Window Management) usually reserved for native code.
3.  **Robust Architecture:** The system must be stable, separating the critical Display Server from the user's potentially unstable JS code.

## 3. Architecture Overview
-   **`webcompositor`**: A minimal Wayland compositor (based on Waylib/wlroots). It manages hardware, inputs, and composes windows. It launches `web-shell` on startup.
-   **`web-shell`**: A QtWebEngine-based Wayland client. It loads the user's HTML/JS and injects the `WebShell` API via `QtWebChannel`.

## 4. Future API Reference (Draft)
The `WebShell` global object will expose the following namespaces, inspired by Quickshell's modular design.

### `WebShell.System`
*General system information and control.*
-   `Clock`: `time`, `timezone`, `uptime`
-   `Power`: `profiles` (Performance, PowerSaver), `shutdown()`, `reboot()`
-   `Screen`: `brightness`, `resolution`, `refreshRate`

### `WebShell.Services`
*Integration with standard Linux desktop services.*
-   `Battery`: `percent`, `state` (Charging/Discharging), `timeToEmpty`
-   `Network`: `wifi` (SSID, strength), `ethernet`, `connectivity` (Online/Offline)
-   `Bluetooth`: `adapters`, `devices`, `connect(device)`, `scan()`
-   `Audio` (Pipewire/Pulse): `volume`, `mute`, `sinks`, `sources`
-   `Media` (MPRIS): `players` (Spotify, VLC), `play()`, `pause()`, `next()`, `metadata`
-   `Notifications`: `server` (host a daemon), `history`, `close(id)`
-   `Tray`: `items` (StatusNotifierItems), `activate(id, x, y)`

### `WebShell.Wayland`
*Interaction with the Wayland Compositor.*
-   `Toplevels`: List of open windows.
-   `Workspaces`: `current`, `list`, `switchTo(id)`
-   `Layers`: Control over layer shell surfaces (panels, wallpapers).
-   `SessionLock`: API to implement a lock screen.

### `WebShell.IO`
*Low-level input/output for advanced scripting.*
-   `Process`: `exec(cmd)`, `spawn(cmd)`, `stdout`, `stdin`
-   `File`: `read(path)`, `write(path)`, `watch(path)`
-   `Socket`: `connect(url)`, `send(data)`

## 5. User Workflow
1.  User creates a directory `~/.config/webshell/`.
2.  User writes `index.html`, `style.css`, and `script.js`.
3.  In `script.js`:
    ```javascript
    import { WebShell } from 'qrc:///qtwebchannel/qwebchannel.js';
    
    new QWebChannel(qt.webChannelTransport, (channel) => {
        const battery = channel.objects.battery;
        
        battery.levelChanged.connect((level) => {
            document.getElementById('battery-icon').innerText = level + '%';
        });
    });
    ```
4.  User runs `webcompositor`. The shell loads their UI.
