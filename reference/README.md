### Core Infrastructure (POC 0)
| Project | URL | Relevance |
|---------|-----|-----------|
| waylib-shared | https://github.com/vioken/waylib | Foundation compositor framework |
| qwlroots | https://github.com/vioken/qwlroots | Qt wrappers for wlroots objects |
| Treeland | https://github.com/linuxdeepin/treeland | Working waylib compositor example |
| wlroots | https://gitlab.freedesktop.org/wlroots/wlroots | Underlying protocol library |

### WebEngine Integration (POC 1)
| Project | URL | Relevance |
|---------|-----|-----------|
| Quickshell + WebEngine patch | (your patch in documents) | CMake pattern for WebEngine enablement |
| Qt WebEngine docs | qt.io | QML WebEngineView integration |
| Qt WebChannel docs | qt.io | QObject ↔ JS bridge mechanics |

### Effect/Visual Reference (Later POCs)
| Project | URL | Relevance |
|---------|-----|-----------|
| SceneFX | https://github.com/wlrfx/scenefx | Blur architecture concepts |
| Vitreus/eqsh | https://github.com/aspect-ux/eqsh | QML shader patterns |
| Hyprland | https://github.com/hyprwm/Hyprland | Blur implementation reference |

### Layout Logic Reference (Later POCs)
| Project | URL | Relevance |
|---------|-----|-----------|
| Scroll | https://github.com/dawsers/scroll | WM logic extraction target |
| niri | https://github.com/YaLTeR/niri | Scrolling layout math |
| PaperWM | https://github.com/paperwm/PaperWM | Infinite canvas concepts |

---

## Research Request for POC 0 and POC 1

I need research agent output on the following **specific documentation**:

### For POC 0 (Skeleton Compositor):
1. **waylib-shared repository**: 
   - Directory structure
   - CMakeLists.txt (root and examples)
   - Minimal example compositor code (if exists)
   - Required Qt6 modules and dependencies

2. **qwlroots repository**:
   - Public API headers (what classes are exposed)
   - How WOutput and WSurface map to Qt types

3. **Treeland repository**:
   - Entry point (main.cpp or equivalent)
   - How it initializes waylib
   - Minimal QML scene setup

### For POC 1 (WebEngine + WebChannel):
4. **Qt 6.x WebEngine QML integration**:
   - WebEngineView QML type properties/signals
   - WebChannel property on WebEngineView
   - Initialization requirements (AA_ShareOpenGLContexts, QtWebEngineQuick::initialize())

5. **Qt 6.x WebChannel C++ side**:
   - QWebChannel registration API
   - QObject exposure pattern
   - Signal/slot bridging to JS

6. **Any existing examples** of QtWebEngine embedded inside a QtQuick compositor context (not standalone browser)

---

## Clarifications Required

1. **waylib-shared vs waylib**: The conversation references a "waylib-shared" fork. Is this https://github.com/vioken/waylib or a separate fork? I need the exact repository URL.

2. **Target Qt version**: Qt 6.6+, 6.7, or 6.8? This affects WebEngine API availability.

3. **Target wlroots version**: waylib-shared tracks which wlroots version? (0.17, 0.18, 0.19?)

4. **Build environment**: Fedora assumed from spec files. Confirm target distro and package manager.

---

Once you provide the research output and clarifications, I will produce the 5 agent backlog files structured as:

```
backlog/
├── agent-1-qt-scaffold/
│   ├── brief.md
│   ├── internals.md
│   └── reference.md
├── agent-2-waylib-minimal/
│   ├── brief.md
│   ├── internals.md
│   └── reference.md
├── agent-3-webengine-embed/
│   ├── brief.md
│   ├── internals.md
│   └── reference.md
├── agent-4-webchannel-bridge/
│   ├── brief.md
│   ├── internals.md
│   └── reference.md
└── agent-5-integration-test/
    ├── brief.md
    ├── internals.md
    └── reference.md
```
