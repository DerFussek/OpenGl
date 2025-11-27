// IndexBuffer.cpp
#include "physics_engine/buffers/IndexBuffer.h"

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
        : m_Count(count)
{
    glGenBuffers(1, &m_ID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 count * sizeof(unsigned int), data, GL_STATIC_DRAW);
}

IndexBuffer::IndexBuffer(IndexBuffer&& o) noexcept
        : m_ID(o.m_ID), m_Count(o.m_Count)
{
    o.m_ID = 0;
    o.m_Count = 0;
}

IndexBuffer& IndexBuffer::operator=(IndexBuffer&& o) noexcept
{
    if (this != &o) {
        glDeleteBuffers(1, &m_ID);
        m_ID    = o.m_ID;
        m_Count = o.m_Count;
        o.m_ID = 0;
        o.m_Count = 0;
    }
    return *this;
}

IndexBuffer::~IndexBuffer()
{
    if (m_ID) glDeleteBuffers(1, &m_ID);
}

void IndexBuffer::UpdateData(const unsigned int* data, unsigned int count)
{
    if (!m_ID) glGenBuffers(1, &m_ID);                // erzeugen, falls Standard­konstruiert
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 count * sizeof(unsigned int), data, GL_STATIC_DRAW);
    m_Count = count;
}

void IndexBuffer::Bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
}

void IndexBuffer::Unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
