#pragma once

#include "physics_engine/rendering/VertexBuffer.h"
#include "physics_engine/rendering/VertexBufferLayout.h"

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