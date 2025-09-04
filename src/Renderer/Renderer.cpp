#include "Renderer/Renderer.h"

#include "VertexBuffer/VertexBuffer.h"
#include "VertexArray/VertexArray.h"
#include "Shader/Shader.h"

#include "Object/Object.h"
#include <glad/glad.h>

void Renderer::Clear() { 
    glClear(GL_COLOR_BUFFER_BIT); 
}


void Renderer::DrawArray(const VertexBuffer &vb, const VertexArray &va, const Shader &shader)
{
    vb.Bind();
    va.Bind();
    shader.Bind();

    glDrawArrays(GL_STATIC_DRAW, 0, vb.getCount());
}

void Renderer::DrawObj(const Object& obj) const {
    obj.render(*this); // *this ist const -> passt zu render(const Renderer&)
}
