#include "VertexBuffer.h"
#include "Renderer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
    GLCALL(glGenBuffers(1, &m_RenderedID));
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, m_RenderedID));
    GLCALL(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer()
{
    GLCALL(glDeleteBuffers(1, &m_RenderedID));
}

void VertexBuffer::Bind() const
{   
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, m_RenderedID));
}

void VertexBuffer::Unbind() const
{   
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
}