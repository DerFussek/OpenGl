#pragma once

#include <array>
#include <vector>
#include <string>

#include "physics_engine/buffers/VertexBuffer.h"
#include "physics_engine/buffers/VertexBufferLayout.h"
#include "physics_engine/buffers/VertexArray.h"
#include "physics_engine/buffers/IndexBuffer.h"
#include "physics_engine/shader/Shader.h"
#include "physics_engine/render/Renderer.h"
#include "physics_engine/objects/ObjectBase.h"

class GlRect final : public ObjectBase {
    private:
        VertexBuffer vb;
        VertexBufferLayout layout;
        VertexArray va;
        IndexBuffer ib;
        Shader shader;

    public:
        float m_PosX = 0.0f;
        float m_PosY = 0.0f;

        std::array<float, 4> m_Color { 1.0f, 1.0f, 1.0f, 1.0f };

        float m_Width  = 1.0f;
        float m_Height = 1.0f;

        std::vector<float> createVertecies(float width, float height) const;

    
        GlRect(); // Standardkonstruktor

        GlRect(const std::string& id,
               float posX, float posY,
               const std::array<float, 4>& color,
               float width, float height);

        ~GlRect() = default;

        void draw(Renderer& r) const override;
        void updateVertecies();

        inline float getX() const { return m_PosX; }
        inline float getY() const { return m_PosY; }
        inline void setPosition(float x, float y) { m_PosX = x; m_PosY = y; }

        inline float getWidth()  const { return m_Width; }
        inline float getHeight() const { return m_Height; }
        inline void setSize(float width, float height) {
            m_Width = width;
            m_Height = height;
            updateVertecies();
        }

        inline std::array<float, 4> getColor() const { return m_Color; }
        inline void setColor(const std::array<float, 4>& color) { m_Color = color; }

        bool contains(float x, float y) const;
};
