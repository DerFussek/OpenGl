#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"

class IndexBuffer {
    private:
        unsigned int m_ID;
        unsigned int m_Count;

    public:
        IndexBuffer() = default;
        IndexBuffer(const unsigned int* data, unsigned int count);
        ~IndexBuffer();

        IndexBuffer(const IndexBuffer&)            = delete;   // kein Kopieren
        IndexBuffer& operator=(const IndexBuffer&) = delete;

        IndexBuffer(IndexBuffer&& other) noexcept;            // Move
        IndexBuffer& operator=(IndexBuffer&& other) noexcept;

        void UpdateData(const unsigned int* data, unsigned int count);
        void Bind() const;
        void Unbind() const;

        inline unsigned int getCount() const {return m_Count;}
};