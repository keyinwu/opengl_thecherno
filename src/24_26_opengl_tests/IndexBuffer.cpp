#include "IndexBuffer.h"
#include "Renderer.h"

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
    : m_Count(count)
{
    ASSERT(sizeof(unsigned int) == sizeof(GLuint));

    GLCALL(glGenBuffers(1, &m_RenderedID));
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RenderedID));
    GLCALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer()
{
    GLCALL(glDeleteBuffers(1, &m_RenderedID));
}

void IndexBuffer::Bind() const
{   
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RenderedID));
}

void IndexBuffer::Unbind() const
{   
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}