#pragma once
#include <array>
#include <vector>

#include "buffers/VertexBuffer.h"
#include "buffers/VertexArray.h"
#include "buffers/IndexBuffer.h"
#include "shader/Shader.h"
#include "buffers/VertexBufferLayout.h"
#include "render/Renderer.h"
#include "render/Drawable.h"

class Rect final : public Drawable {
    private:
        VertexBuffer vb;
        VertexBufferLayout layout;
        VertexArray va;
        IndexBuffer ib;
        Shader shader;

        
        std::array<float, 2> m_Pos;
        std::array<float, 4> m_Color;
        std::array<float, 2> m_Size;

    public:
        Rect(std::array<float, 2>pos, std::array<float, 4>color, std::array<float, 2>size);
        ~Rect() = default;

        void draw(Renderer& r) const override;
        std::vector<float> createVertecies(std::array<float, 2>size);    
};