#ifndef RENDERER_H__
#define RENDERER_H__

#include <glad/glad.h>
#include <iostream>

using namespace std;

#define ASSERT(x) if (!(x)) assert(false)
#define GLCALL(x) GLClearError();\
    x;\
    ASSERT(GLCheckErro())

void GLClearError();
bool GLCheckErro();
// bool GLLogCall(const char* function, const char* file, int line);

#endif