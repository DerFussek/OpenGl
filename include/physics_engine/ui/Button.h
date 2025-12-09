#pragma once

#include <functional>
#include "physics_engine/ui/UIElement.h"
#include "physics_engine/objects/Updateable.h"

namespace PhyEn {

class Button : public UIElement, public Updateable {
public:
    using Callback = std::function<void()>;

    Button(const glm::vec2& position,
           const glm::vec2& size,
           const glm::vec4& color,
           Callback onClick)
        : UIElement(position, size, color),
          m_onClick(std::move(onClick))
    {}

    void update(float /*dt*/) override;
    void onMouseEvent(const glm::vec2& mousePos, bool pressed);

private:
    Callback m_onClick;
    bool m_hovered {false};
    bool m_pressed {false};
};

} // namespace pe
