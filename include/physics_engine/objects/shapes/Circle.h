#pragma once

#include <vector>
#include <array>

#include "physics_engine/buffers/VertexBuffer.h"
#include "physics_engine/buffers/VertexBufferLayout.h"
#include "physics_engine/buffers/VertexArray.h"
#include "physics_engine/buffers/IndexBuffer.h"
#include "physics_engine/shader/Shader.h"
#include "physics_engine/render/Renderer.h"
#include "physics_engine/objects/ObjectBase.h"

class Circle final : public ObjectBase {
    private:
        VertexBuffer vb;
        VertexBufferLayout layout;
        VertexArray va;
        IndexBuffer ib;
        Shader shader;

        
        std::array<float, 2> m_Pos;
        std::array<float, 4> m_Color;

        float m_Radius;
        int m_Res = 32;

    public:
        Circle(const std::string& id, std::array<float,2>position, std::array<float,4>color, float radius);
        ~Circle() = default;

       
        void draw(Renderer& r) const override;
        void createVertecies(float radius, int res, std::vector<float> &vertecies);
        void updateVertecies();

        const inline int getRes() { return m_Res; }
        inline void setResulution(int res) { if(res >= 0) m_Res = res; }

        const inline std::array<float, 2>getPosition() { return m_Pos; }
        inline void setPosition(std::array<float, 2>pos) { m_Pos = pos; }

        const inline std::array<float, 4>getColor() { return m_Color; }
        inline void setColor(std::array<float, 4>color) { m_Color = color; }
};
