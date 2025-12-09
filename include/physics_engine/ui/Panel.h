#pragma once

#include "physics_engine/ui/UIElement.h"

namespace PhyEn {

class Panel : public UIElement {
    public:
        Panel(const glm::vec2& position,
            const glm::vec2& size,
            const glm::vec4& color)
            : UIElement(position, size, color) {}
    };

} // namespace pe
