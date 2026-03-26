# Sustify

Sustify is a lightweight, local audio player application built with a C++ backend and a modern web-based frontend. It leverages the OS-native WebView to render the UI, keeping the application footprint small and performant.

## Features
* **Web based UI:** Frontend built with standard HTML, CSS, and JavaScript.
* **Audio Playback:** Core audio handling and queue management written in C++.
* **Metadata Extraction:** Reads ID3 tags (artist, title) directly from audio files using TagLib.
* **Standalone Executable:** Automated build pipeline packages the executable, required DLLs, and GUI assets into a single portable directory.

## Architecture
* **Backend:** C++17 / C++20
* **Frontend:** OS-Native WebView (via `webview/webview`)
* **Build System:** CMake
* **Package Management:** vcpkg

## Prerequisites
To build Sustify from source on Windows, you will need the following installed:
1. **Visual Studio 2022** (with Desktop development with C++ workload)
2. **CMake** (version 3.10 or higher)
3. **vcpkg** (C++ Library Manager)

### Required Libraries
You must install `taglib` via vcpkg before building. `zlib` will be installed automatically as a dependency.
```bash
vcpkg install taglib:x64-windows
```

## Project Structure
```
Sustify/
├── CMakeLists.txt      # Build configuration and automated asset syncing
├── main.cpp            # Application entry point
├── resources.rc        # Windows resource script for the application icon
├── gui/                # Frontend assets (HTML, CSS, JS, images)
├── src/                # C++ source files (window.cpp, audio.cpp, etc.)
├── headers/            # Project header files
└── include/            # External include directories
```

## Building the Project
1. Clone the repository and navigate to the project root.
2. Configure the project with CMake, pointing it to your vcpkg toolchain file. Replace <path-to-vcpkg> with your actual vcpkg installation path:
```
cmake -B out/build/x64-Release -S . -DCMAKE_TOOLCHAIN_FILE="<path-to-vcpkg>/scripts/buildsystems/vcpkg.cmake"
cmake --build out/build/x64-Release --config Release
```


