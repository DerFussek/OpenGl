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

class Circle : public Drawable {
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
        Circle(std::array<float,2>position, std::array<float,4>color, float radius);
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
