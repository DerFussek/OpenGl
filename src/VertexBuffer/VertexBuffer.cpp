#include "VertexBuffer/VertexBuffer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int sizeBytes)
    : m_RendererID(0), m_Size(sizeBytes)
{
    glGenBuffers(1, &m_RendererID);
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    glBufferData(GL_ARRAY_BUFFER, sizeBytes, data, GL_STATIC_DRAW);
}

VertexBuffer::VertexBuffer()
    : m_RendererID(0), m_Size(0)
{
    glGenBuffers(1, &m_RendererID);
}

VertexBuffer::~VertexBuffer()
{
    if (m_RendererID) glDeleteBuffers(1, &m_RendererID);
}

void VertexBuffer::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
}

void VertexBuffer::Unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::ChangeData(const void* data, unsigned int sizeBytes)
{
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    glBufferData(GL_ARRAY_BUFFER, sizeBytes, data, GL_DYNAMIC_DRAW);
    m_Size = sizeBytes;
}

unsigned int VertexBuffer::getCount() const {
    return m_Size / sizeof(float) / 2; 
}