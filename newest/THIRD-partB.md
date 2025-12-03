# Part B: The Bridge & The Python Parallel

## Analyzing the Python `WebView`
The snippet provided is a classic "Bridge" pattern:
```python
class WebView(..., open_bridge=True):
    def expose_function(self, func): ...
```
*   **`open_bridge=True`**: This injects a global JS object (usually `window.py` or `window.bridge`).
*   **`expose_function`**: This registers a callback. When JS calls `bridge.myFunc()`, it serializes args to JSON, sends them to Python, Python executes, and returns the result.

## Mapping to WebShell (QtWebChannel)
Our architecture is the **exact C++ equivalent** of this Python class.

| Concept | Python/GTK Example | WebShell (Qt) |
| :--- | :--- | :--- |
| **Enable Bridge** | `open_bridge=True` | `channel.registerObject(...)` |
| **Expose API** | `expose_function(func)` | `Q_INVOKABLE` methods & `Q_PROPERTY` |
| **JS Access** | `window.bridge.func()` | `channel.objects.system.func()` |
| **Security** | "Security warning" | Same. Only expose to `file://` or trusted internal URLs. |

## What We Learn
1.  **Explicit Exposure:** Just like the Python class requires you to manually `expose_function`, we must manually register every C++ service. There is no "magic" that exposes the whole OS.
2.  **The "Inspector":** The Python class has `open_inspector`. We must enable the **DevTools** port (usually 9222 or an embedded inspector) because debugging the Shell UI (HTML/JS) is impossible without it.
3.  **Properties vs Functions:** The Python example seems function-centric. QtWebChannel is **Property-centric** (Signals/Slots). This is better for UI state (e.g., `battery.level` changes automatically) rather than polling via functions.
