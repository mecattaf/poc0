# Design Decisions

## 1. Multi-Process Architecture
**Decision:** Split the application into two distinct processes: `webcompositor` (Host) and `web-shell` (Client).

**Rationale:**
-   **Technical Necessity:** `QtWebEngine` requires a standard desktop QPA (like `xcb` or `wayland`) to initialize its GPU process correctly. `Waylib` requires a custom QPA to function as a compositor. These are mutually exclusive in a single process.
-   **Stability:** A crash in the web content (common in browsers) will not bring down the entire display server. The compositor can detect the client crash and restart it.
-   **Security:** The massive attack surface of a browser engine is isolated in a standard unprivileged Wayland client, rather than running with the high privileges of the compositor (DRM/KMS access).

## 2. QtWebChannel as the Bridge
**Decision:** Use `QtWebChannel` as the primary mechanism to expose native functionality to the JavaScript runtime.

**Rationale:**
-   **Native Integration:** It is the standard, supported way to bridge C++ and JS in QtWebEngine.
-   **Asynchronous:** Operations don't block the UI thread, essential for a smooth 60fps shell experience.
-   **Type Safety:** C++ Signals/Slots are automatically mapped, reducing the boilerplate of manual string parsing (JSON-RPC).

## 3. "Quickshell-inspired" API Design
**Decision:** Structure the JavaScript API to mirror the modular, capability-based design of `Quickshell`.

**Rationale:**
-   **Familiarity:** Adopts a proven model for shell customization (Services, System, Wayland namespaces).
-   **Modularity:** Users only import what they need. A battery widget doesn't need access to file system APIs.
-   **Declarative Nature:** While the logic is imperative JS, the API will expose properties (Signals) that allow for reactive UI updates (e.g., `System.battery.level` changes automatically update the DOM).

## 4. Smart Client, Dumb Compositor
**Decision:** Move the bulk of the "Shell" logic (System Tray, Clock, Battery, Network) into the `web-shell` client process. The `webcompositor` is strictly a display server and window manager.

**Rationale:**
-   **Simplicity:** The compositor code remains minimal and stable.
-   **Flexibility:** The shell can be completely replaced or updated without restarting the display server.
-   **IPC Reduction:** Most "shell" features (reading battery, checking time) don't actually need the Compositor. They just need Linux system APIs, which the `web-shell` process can access directly.
