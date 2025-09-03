#pragma once

#include <iostream>
#include <vector>
#include "glad/glad.h"
#include "GLFW/glfw3.h"

struct VertexBufferElement {
    unsigned int type;
    unsigned int count;
    unsigned char normalized;

    VertexBufferElement(unsigned int type, unsigned int count, unsigned char normalized) {
        this->count = count;
        this->type = type;
        this->normalized = normalized;
    }

    static unsigned int GetSizeOfType(unsigned int type) {
        switch (type)
        {
            case GL_FLOAT:          return 4;
            case GL_UNSIGNED_INT:   return 4;
            case GL_UNSIGNED_BYTE:  return 1;
            default: return -1;
        }
        _ASSERT(false);
    }
};

class VertexBufferLayout {

    private:
        std::vector<VertexBufferElement> m_Elements;
        unsigned int m_Stride;
    
    public:
        VertexBufferLayout();

        template<typename T>
        void Push(unsigned int count);

        template<>
        void Push<float>(unsigned int count);

        template<>
        void Push<unsigned int>(unsigned int count);

        template<>
        void Push<unsigned char>(unsigned int count);

        inline const std::vector<VertexBufferElement> GetElements() const {return m_Elements;}
        inline unsigned int GetStride() const { return m_Stride;}
};


