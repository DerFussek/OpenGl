#pragma once

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class VertexBuffer {
    private:
        unsigned int m_RendererID;
        unsigned int m_Size;

    public:
        VertexBuffer(const void* data, unsigned int size);
        VertexBuffer();
        ~VertexBuffer();

        void Bind() const;
        void Unbind() const;
        void ChangeData(const void *data, unsigned int size);

        inline unsigned int getSize() const {return m_Size;}
        inline unsigned int getCount() const;

};