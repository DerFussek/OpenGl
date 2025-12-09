#pragma once

#include <glm/glm.hpp>
#include <memory>
#include "physics_engine/objects/Drawable.h"
#include "physics_engine/rendering/VertexBuffer.h"
#include "physics_engine/rendering/VertexArray.h"
#include "physics_engine/rendering/IndexBuffer.h"

namespace PhyEn {
    struct ShapeVertex {
        glm::vec2 position;
        glm::vec2 textCoord;
    };

    class GlShape : public Drawable {
        private:
            std::unique_ptr<VertexArray> m_vao;
            std::unique_ptr<VertexBuffer> m_vbo;
            std::unique_ptr<IndexBuffer> m_ibo;

            glm::vec2 m_position {0.0f};
            glm::vec2 m_scale {1.0f};
            float m_rotation {0.0f};

            glm::vec4 m_color {1.0f};
        
        public:
            GlShape(const ShapeVertex* vertecies, 
                    size_t vertexCount, 
                    const unsigned int* indices,
                    size_t indexCount,
                    const glm::vec4& color);

        public:
            void setTransform(const glm::vec2& position, float rotation, const glm::vec2& scale);
            void setColor(const glm::vec4& color) { m_color = color; }

            const glm::vec2& position() const { return m_position; }
            float rotation() const { return m_rotation; }
            const glm::vec2& scale() const { return m_scale; }
            const glm::vec4& color() const { return m_color; }

            VertexArray& vao() { return *m_vao; }
            IndexBuffer& ibo() { return *m_ibo; }

            void draw(Renderer2D& renderer) override;
    };
}