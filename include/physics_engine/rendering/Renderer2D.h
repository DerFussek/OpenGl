#pragma once

#include <glm/glm.hpp>
#include "physics_engine/rendering/Shader.h"

namespace PhyEn {

class GlShape;

class Renderer2D {
    private:
        Shader* m_shapeShader;
        glm::mat4 m_viewProj;

    public:
    Renderer2D(Shader* shapeShader);

    void begin(const glm::mat4& viewProj);
    void submit(GlShape& shape);
    void end();
};

} // namespace pe
