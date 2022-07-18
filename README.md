# OpenGL Learning

This repository is based on GLFW and GLAD running on MacOS. 

Check the branches to see the progress of the episodes.

### GLFW and GLAD Setup

Install GLFW by the command `brew install glfw`.

Download GLAD zip file from the [official website](https://glad.dav1d.de).

Put library files into the workspace directory:
```
 __ workspace
   |__ dependencies
     |__ include
       |__ glad
         |__ glad.h
       |__ GLFW
         |__ glfw3.h
         |__ glfw3native.h
       |__ glm
       |__ KHR
         |__ khrplatform.h
       |__ stb_image
         |__ stb_image.h
     |__ library
       |__ libglfw.3.3.dylib
   |__ src
     |__ vendor
       |__ imgui
       |__ glad.c
       |__ stb_image.cpp
```
* The library version needs to be consistent with the downloaded.

Library files the `main` branch used are included in the branch `dependencies-main`.

Aside from the library files, it needs extra configuration in `tasks.json` in VS Code:

 ```json
 // Final Version
 "args": [
   "-std=c++17",
   "-fdiagnostics-color=always",
   "-Wall",
   "-g",
   "-I${workspaceFolder}/dependencies/include",
   "-I${workspaceFolder}/src/vendor",
   "-I${workspaceFolder}/src",
   "-L${workspaceFolder}/dependencies/library",
   "${workspaceFolder}/dependencies/library/libglfw.3.3.dylib",
   "${workspaceFolder}/src/*.cpp",
   "${workspaceFolder}/src/vendor/*.c",
   "${workspaceFolder}/src/vendor/*.cpp",
   "${workspaceFolder}/src/tests/*.cpp",
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

### Contents

This repository follows the [OpenGL Tutorial by The Cherno](https://www.youtube.com/watch?v=W3gAzLwfIP0&list=PLlrATfBNZ98foTJPJ_Ev03o2oq3-GGOS2). To clarify, the original demo is based on GLEW and runs on Windows. Here, it's using GLAD instead and running on MacOS.
