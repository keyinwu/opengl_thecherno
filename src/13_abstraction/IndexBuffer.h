#ifndef INDEXBUFFER_H__
#define INDEXBUFFER_H__

class IndexBuffer
{
private:
    unsigned int m_RenderedID;
    unsigned int m_Count;
public:
    IndexBuffer(const unsigned int* data, unsigned int count);
    ~IndexBuffer();

    void Bind() const;
    void Unbind() const;

    inline unsigned int GetCount() const {return m_Count;}
};

#endif