# ep17-textures

VS Code `tasks.json` for ep17-ep21:

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
    "${workspaceFolder}/src/vendor/*.c",
    "${workspaceFolder}/src/vendor/*.cpp",
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

