#ifndef RENDERER_H__
#define RENDERER_H__

#include <glad/glad.h>
#include <iostream>

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Utils.h"

using namespace std;

#define GLCALL(x) GLClearError();\
    x;\
    ASSERT(GLCheckErro())

class Renderer
{
public:
    void Clear() const;
    void BgColor(float v0, float v1, float v2, float v3);
    void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
};

void GLClearError();
bool GLCheckErro();
// bool GLLogCall(const char* function, const char* file, int line);

#endif