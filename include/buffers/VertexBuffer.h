#pragma once

#include "glad/glad.h"
#include "GLFW/glfw3.h"

class VertexBuffer {
    private:
        unsigned int m_ID;
        unsigned int m_Size;

    public:
        VertexBuffer() = default;                                 // Standard­konstruktor
        VertexBuffer(const void* data, unsigned int size);
        ~VertexBuffer();

        VertexBuffer(const VertexBuffer&)            = delete;
        VertexBuffer& operator=(const VertexBuffer&) = delete;
        VertexBuffer(VertexBuffer&& other) noexcept;
        VertexBuffer& operator=(VertexBuffer&& other) noexcept;

        void Bind() const;
        void Unbind() const;

        void UpdateData(const void* data, unsigned int size);

        inline unsigned int getSize() const { return m_Size; }
        inline unsigned int getCount() const { return m_Size / sizeof(float) / 2; } 
};