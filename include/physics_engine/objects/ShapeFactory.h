#pragma once

#include <memory>
#include <glm/glm.hpp>
#include "physics_engine/objects/GlShape.h"

namespace PhyEn {

    class ShapeFactory {
    public:
        static std::unique_ptr<GlShape> createRect(const glm::vec2& size,
                                                const glm::vec4& color);

        static std::unique_ptr<GlShape> createCircle(float radius,
                                                    int segments,
                                                    const glm::vec4& color);
    };

} // namespace pe
