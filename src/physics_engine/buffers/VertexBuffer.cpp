// VertexBuffer.cpp
#include "physics_engine/buffers/VertexBuffer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size)
        : m_Size(size)
{
    glGenBuffers(1, &m_ID);
    glBindBuffer(GL_ARRAY_BUFFER, m_ID);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VertexBuffer::VertexBuffer(VertexBuffer&& o) noexcept
        : m_ID(o.m_ID), m_Size(o.m_Size)
{
    o.m_ID = 0;
    o.m_Size = 0;
}

VertexBuffer& VertexBuffer::operator=(VertexBuffer&& o) noexcept
{
    if (this != &o) {
        glDeleteBuffers(1, &m_ID);
        m_ID   = o.m_ID;
        m_Size = o.m_Size;
        o.m_ID = 0;
        o.m_Size = 0;
    }
    return *this;
}

VertexBuffer::~VertexBuffer()
{
    if (m_ID) glDeleteBuffers(1, &m_ID);
}

void VertexBuffer::UpdateData(const void* data, unsigned int size)
{
    if (!m_ID) glGenBuffers(1, &m_ID);               // erzeugen, falls Standard­konstruiert
    glBindBuffer(GL_ARRAY_BUFFER, m_ID);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
    m_Size = size;
}

void VertexBuffer::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_ID);
}

void VertexBuffer::Unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
