# OpenGL Learning

 This repository is based on GLFW and GLAD running on MacOS. 

 ### GLFW and GLAD Setup

 Aside from the library files included in the repo, it needs extra configuration in `tasks.json` in VS Code:

     ```json
     ...
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
       "${workspaceFolder}/app",
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
       "-Wno-deprecated"
     ],
     ...
     ```

 ### Contents

 This repository follows the [OpenGL Tutorial by The Cherno](https://www.youtube.com/watch?v=W3gAzLwfIP0&list=PLlrATfBNZ98foTJPJ_Ev03o2oq3-GGOS2). To clarify, the original demo is based on GLEW and runs on Windows. Here, it's using GLAD instead and running on MacOS.
