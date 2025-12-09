#include "physics_engine/objects/GlShape.h"
#include "physics_engine/rendering/VertexBufferLayout.h"
#include "physics_engine/rendering/Renderer2D.h"

namespace PhyEn {
    GlShape::GlShape(const ShapeVertex* vertices,
                     size_t vertexCount,
                     const unsigned int* indices,
                     size_t indexCount,
                     const glm::vec4& color)
                     : m_color(color)
    {
        m_vao = std::make_unique<VertexArray>();
        m_vbo = std::make_unique<VertexBuffer>(vertices,
                                            vertexCount * sizeof(ShapeVertex));
        VertexBufferLayout layout;
        layout.Push<float>(2); // position
        layout.Push<float>(2); // texCoord
        m_vao->AddBuffer(*m_vbo, layout);

        m_ibo = std::make_unique<IndexBuffer>(indices,
                                              static_cast<unsigned int>(indexCount));
    }

    void GlShape::setTransform(const glm::vec2& position, float rotation, const glm::vec2& scale) {
        m_position = position;
        m_rotation = rotation;
        m_scale    = scale;
    }

    void GlShape::draw(Renderer2D& renderer) {
        renderer.submit(*this);
    }

}