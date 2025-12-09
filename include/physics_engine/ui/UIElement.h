#pragma once

#include <glm/glm.hpp>
#include <memory>
#include "physics_engine/objects/Drawable.h"
#include "physics_engine/objects/GlShape.h"
#include "physics_engine/objects/ShapeFactory.h"

namespace PhyEn {

class UIElement : public Drawable {
    protected:
        std::unique_ptr<GlShape> m_shape;

    public:
        UIElement(const glm::vec2& position,
                const glm::vec2& size,
                const glm::vec4& color);

        void setPosition(const glm::vec2& pos);
        void setSize(const glm::vec2& size);
        void setColor(const glm::vec4& color);

        void draw(Renderer2D& renderer) override;
};

} // namespace pe
