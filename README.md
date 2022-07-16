# ep22-imgui

The compiler will also need glm library under `dependencies/include`, as shown in the `dependencies-main`.

VS Code `tasks.json`:

  ```json
  "args": [
    "-std=c++17",
    "-fdiagnostics-color=always",
    "-Wall",
    "-g",
    "-I${workspaceFolder}/dependencies/include",
    "-I${workspaceFolder}/src/vendor",
    "-L${workspaceFolder}/dependencies/library",
    "${workspaceFolder}/dependencies/library/libglfw.3.3.dylib",
    "${workspaceFolder}/src/*.cpp",
    "${workspaceFolder}/src/vendor/*.c",
    "${workspaceFolder}/src/vendor/*.cpp",
    "${workspaceFolder}/src/vendor/imgui/*.cpp",
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

