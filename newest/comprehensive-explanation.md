# Comprehensive Explanation: The WebShell Ecosystem

## The "Why"
Building a custom desktop environment on Linux is historically hard. You either learn C++/Rust and fight with Wayland protocols, or you use rigid widgets in existing shells (GNOME extensions, KDE Plasmoids). **WebShell** changes this. It gives you the blank canvas of a browser engine—the most flexible UI renderer in existence—and pipes native system power directly into it.

## How It Works: The Lifecycle

### 1. Bootstrapping (`webcompositor`)
When you run the `webcompositor` binary:
1.  **Hardware Init:** It initializes the GPU (DRM/KMS) and input devices (libinput) using `wlroots`.
2.  **Wayland Socket:** It creates a Wayland display socket (e.g., `wayland-1`).
3.  **Client Launch:** It immediately spawns the `web-shell` subprocess, passing the socket name.
4.  **Compositor Loop:** It enters its main event loop, waiting for surfaces to compose. It is configured to treat the `web-shell` window specially—it is the "root" window, always fullscreen, with no decorations.

### 2. The Shell Runtime (`web-shell`)
The `web-shell` process starts up as a standard Wayland client:
1.  **QtWebEngine Init:** It spins up the Chromium engine. Because it's a separate process, it uses the standard Qt Wayland plugin, avoiding the initialization conflicts of the past.
2.  **Object Registration:** It instantiates C++ classes for every supported API (Battery, Network, etc.) and registers them with `QtWebChannel`.
3.  **UI Load:** It loads the user's `index.html`.
4.  **Bridge Injection:** It injects the `qt.webChannelTransport` object into the JavaScript context.

### 3. The User Experience (JavaScript)
Inside the web page, the user's JavaScript takes over:
1.  **Connection:** The script establishes a connection to the `QWebChannel`.
2.  **Proxy Generation:** The channel creates JavaScript proxy objects for every registered C++ object.
3.  **Reactivity:** The user binds these objects to the DOM.
    *   *Example:* When the C++ `Battery` object emits a `levelChanged` signal, the `QtWebChannel` library catches it and invokes the JavaScript callback defined by the user. The user updates a `<div>` text.
    *   *Example:* When the user clicks a "Reboot" button, the JS calls `system.reboot()`. The signal travels over the IPC bridge to C++, which executes the actual Linux command.

## The "Quickshell" Inspiration
We are modeling our API after **Quickshell** because it solved the "taxonomy" problem. It categorized the chaotic world of Linux desktop APIs into logical buckets (`System`, `Services`, `Wayland`).

However, where Quickshell uses QML (a Qt-specific declarative language), **WebShell uses the Web Platform**.
-   Instead of `Rectangle { }`, you use `<div style="background: red">`.
-   Instead of `MouseArea { }`, you use `element.addEventListener('click', ...)`.
-   Instead of `import Quickshell`, you use `channel.objects.quickshell`.

This opens the door to the entire npm ecosystem. You can use React, Vue, Svelte, or Three.js to build your desktop shell. You can use Tailwind CSS for styling. The barrier to entry drops from "Learn C++/QML" to "Know basic HTML."
