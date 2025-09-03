// Renderer.cpp
#include "Renderer.h"
#include "Object.h"
#include <glad/glad.h>

void Renderer::Clear() { glClear(GL_COLOR_BUFFER_BIT); }

void Renderer::Draw(const Object& obj) const {
    obj.render(*this); // *this ist const -> passt zu render(const Renderer&)
}
