#include "Renderer.h"


void Renderer::Clear() const
{
    GLCALL(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::BgColor(float v0, float v1, float v2, float v3)
{
    GLCALL(glClearColor(v0, v1, v2, v3));
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
    shader.Bind();
    va.Bind();
    ib.Bind();
    GLCALL(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr)); // default to be unsigned int
}


// opengl error handling
// ---------------------
void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

bool GLCheckErro() 
{
    while (GLenum error = glGetError())
    {
        cout << "[OpenGL Error] (" << error << "): ";
        switch(error) 
        {
            case GL_INVALID_ENUM :
                cout << "GL_INVALID_ENUM";
                break;
            case GL_INVALID_VALUE :
                cout << "GL_INVALID_VALUE";
                break;
            case GL_INVALID_OPERATION :
                cout << "GL_INVALID_OPERATION";
                break;
            case GL_INVALID_FRAMEBUFFER_OPERATION :
                cout << "GL_INVALID_FRAMEBUFFER_OPERATION";
                break;
            case GL_OUT_OF_MEMORY :
                cout << "GL_OUT_OF_MEMORY";
                break;
            default :
                cout << "Unrecognized error" << error;
        }
        cout << endl;
        return false;
    }
    return true;
}

/*
static bool GLLogCall(const char* function, const char* file, int line)
{
    while (GLenum error = glGetError())
    {
        cout << "[OpenGL Error] (" << error << "): " << function <<
            " " << file << ": " << line << endl;
        return false;
    }
    return true;
}
*/