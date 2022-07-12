#ifndef VERTEXBUFFER_H__
#define VERTEXBUFFER_H__

class VertexBuffer
{
private:
    unsigned int m_RenderedID;
public:
    VertexBuffer(const void* data, unsigned int size);
    ~VertexBuffer();

    void Bind() const;
    void Unbind() const;
};

#endif