# Part B: Patterns & Lessons from DankMaterialShell

## The Pattern: "Backend Daemon + Frontend Shell"
`dankmaterialshell` separates concerns rigorously:
*   **Core (Go):** The "Backend". It handles the heavy lifting—DBus communication, system stats, window management logic, config parsing. It exposes a clean API.
*   **Quickshell (QML):** The "Frontend". It is purely presentation. It binds to the Backend's API and renders the UI.

## Lesson 1: The "Thick" Client
In our `WebShell` architecture, the C++ process (`web-shell`) must act as the **Core**.
*   **Mistake to Avoid:** Don't write system logic in JavaScript. JS is single-threaded and UI-blocking.
*   **Correct Pattern:**
    *   **C++:** Polls battery info in a background thread. Emits `batteryChanged(98)`.
    *   **JS:** Receives signal. Updates DOM. 0ms latency.

## Lesson 2: Modular Services
`dankmaterialshell` organizes code into `Services` (Bluetooth, Audio, Network).
*   **Application:** We should mirror this in our C++ structure.
    *   `src/client/services/BatteryService.cpp` -> Exposes `WebShell.Services.Battery`
    *   `src/client/services/NetworkService.cpp` -> Exposes `WebShell.Services.Network`
*   **Benefit:** This makes the API discoverable and manageable.

## Lesson 3: IPC is King
`dankmaterialshell` likely uses an IPC mechanism (Socket/DBus) to talk between its Go backend and the QML frontend (or Quickshell's internal bindings).
*   **Our Equivalent:** `QtWebChannel`.
*   **Critical Insight:** The API must be **Asynchronous**.
    *   *Bad:* `let files = System.listFiles('/tmp')` (Blocks UI)
    *   *Good:* `System.listFiles('/tmp').then(files => ...)` (Promise-based)
    *   *QtWebChannel Note:* It is inherently async. We must design our JS SDK to wrap these raw channel calls in nice Promises.

## Lesson 4: "Do Not Need Compositor Integration"
You mentioned `dankmaterialshell` ships backend IPC that "does not need compositor integration."
*   **Meaning:** It talks to *standard Linux APIs* (UPower, NetworkManager, PulseAudio), not the Wayland Compositor.
*   **Takeaway:** 90% of a "Shell" is just a Linux System Monitor. Only 10% (Workspaces, Window List) requires talking to the Compositor.
*   **Strategy:** Our `web-shell` C++ backend should implement these standard Linux clients directly. It doesn't need to ask `webcompositor` for battery status. It asks `UPower` (via DBus).
