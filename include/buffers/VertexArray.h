#pragma once

#include "buffers/VertexBuffer.h"
#include "buffers/VertexBufferLayout.h"

class VertexArray {
    private:
        unsigned int m_ID;
    
    public:
        VertexArray();
        ~VertexArray();

        void AddBuffer(const VertexBuffer &vb, const VertexBufferLayout &layout);

        void Bind() const;
        void Unbind() const;
};