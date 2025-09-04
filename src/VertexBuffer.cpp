#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int sizeBytes)
    : m_RendererID(0), m_Size(sizeBytes)
{
    glGenBuffers(1, &m_RendererID);
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    glBufferData(GL_ARRAY_BUFFER, sizeBytes, data, GL_STATIC_DRAW);
}

VertexBuffer::VertexBuffer()
    : m_RendererID(0), m_Size(0) // ✅ init
{
    glGenBuffers(1, &m_RendererID); // ✅ auch hier erzeugen
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
    glBindBuffer(GL_ARRAY_BUFFER, 0); // ✅ nicht NULL
}

void VertexBuffer::ChangeData(const void* data, unsigned int sizeBytes)
{
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    glBufferData(GL_ARRAY_BUFFER, sizeBytes, data, GL_DYNAMIC_DRAW); // 🔁 häufiger Update —> DYNAMIC
    m_Size = sizeBytes; // ✅ m_Size setzen
}

unsigned int VertexBuffer::getCount() const {
    return m_Size / sizeof(float) / 2; 
    // falls du 2 floats pro Vertex (x,y) hast
}

