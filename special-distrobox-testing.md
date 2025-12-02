we set up a fresh distrobox with fedora 43
```

sudo dnf update

sudo dnf install \
    cmake gcc-c++ git ninja-build pkg-config \
    qt6-qtbase-devel qt6-qtdeclarative-devel qt6-qtquickcontrols2-devel \
    qt6-qtshadertools-devel qt6-qtwebengine-devel qt6-qtwebchannel-devel \
    qt6-qtbase-private-devel qt6-qtdeclarative-private-devel \
    wayland-devel wlroots-devel wayland-protocols-devel wlr-protocols-devel \
    libdrm-devel pixman-devel libxkbcommon-devel \
    qwlroots-devel
```

then cd'd into the repo we do 
```
cmake -B build -DCMAKE_BUILD_TYPE=Debug -DCMAKE_SKIP_INSTALL_RULES=ON
cmake --build build -j$(nproc)
```
