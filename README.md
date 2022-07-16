# ep08-shaders

VS Code `tasks.json` for ep08-ep16:

```json
  "args": [
    "-std=c++17",
    "-fdiagnostics-color=always",
    "-Wall",
    "-g",
    "-I${workspaceFolder}/dependencies/include",
    "-L${workspaceFolder}/dependencies/library",
    "${workspaceFolder}/dependencies/library/libglfw.3.3.dylib",
    "${workspaceFolder}/src/*.cpp",
    "${workspaceFolder}/src/glad.c",
    "-o",
    "${workspaceFolder}/src/app",
    "-framework",
    "OpenGL",
    "-framework",
    "Cocoa",
    "-framework",
    "IOKit",
    "-framework",
    "CoreVideo",
    "-framework",
    "CoreFoundation",
    "-Wno-deprecated",
    "-Wno-int-to-void-pointer-cast"
  ],
```
