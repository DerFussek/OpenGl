// Renderer2D.cpp
#include "physics_engine/rendering/Renderer2D.h"
#include "physics_engine/objects/GlShape.h"
#include "physics_engine/rendering/VertexArray.h"
#include "physics_engine/rendering/IndexBuffer.h"
#include <glm/gtc/matrix_transform.hpp>

namespace PhyEn {

Renderer2D::Renderer2D(Shader* shapeShader)
    : m_shapeShader(shapeShader)
{}

void Renderer2D::begin(const glm::mat4& viewProj)
{
    m_viewProj = viewProj;

    m_shapeShader->bind();
    m_shapeShader->setUniform1i("u_UseTexture", 0);
    m_shapeShader->setUniform1i("u_Texture", 0);

    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
}

void Renderer2D::submit(GlShape& shape)
{
    glm::mat4 model(1.0f);
    model = glm::translate(model, glm::vec3(shape.position(), 0.0f));
    model = glm::rotate(model, shape.rotation(), glm::vec3(0, 0, 1));
    model = glm::scale(model, glm::vec3(shape.scale(), 1.0f));

    glm::mat4 mvp = m_viewProj * model;

    m_shapeShader->setUniformMat4f("u_MVP", mvp);
    m_shapeShader->setUniform4f("u_Color",
                                shape.color().r,
                                shape.color().g,
                                shape.color().b,
                                shape.color().a);

                                
    shape.vao().Bind();
    shape.ibo().Bind();

    glDrawElements(GL_TRIANGLES,
                   shape.ibo().getCount(),
                   GL_UNSIGNED_INT,
                   nullptr);
}

void Renderer2D::end()
{
    // optional
}

} // namespace pe
