#pragma once

#include <array>
#include <vector>

#include "physics_engine/buffers/VertexBuffer.h"
#include "physics_engine/buffers/VertexBufferLayout.h"
#include "physics_engine/buffers/VertexArray.h"
#include "physics_engine/buffers/IndexBuffer.h"
#include "physics_engine/shader/Shader.h"
#include "physics_engine/render/Renderer.h"
#include "physics_engine/objects/ObjectBase.h"


class Rect final : public ObjectBase {
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
        Rect(std::string& id, std::array<float, 2>pos, std::array<float, 4>color, std::array<float, 2>size);
        ~Rect() = default;

        void draw(Renderer& r) const override;
        void updateVertecies();
        std::vector<float> createVertecies(std::array<float, 2>size);    

        const inline std::array<float, 2>getSize() { return m_Size; }
        inline void setSize(std::array<float, 2>size) { m_Size = size; }

        const inline std::array<float, 2>getPosition() { return m_Pos; }
        inline void setPosition(std::array<float, 2>pos) { m_Pos = pos; }

        const inline std::array<float, 4>getColor() { return m_Color; }
        inline void setColor(std::array<float, 4>color) { m_Color = color; }

};