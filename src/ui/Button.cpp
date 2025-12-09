#include "physics_engine/ui/Button.h"

namespace PhyEn {

    void Button::update(float) {
            // hier z.B. Hover-Farbe etc. setzen
    }

    void Button::onMouseEvent(const glm::vec2& mousePos, bool pressed) {
        // einfache AABB-Hit-Detection; Position/Größe aus Shape ableiten
        glm::vec2 pos   = m_shape->position();
        glm::vec2 half  = m_shape->scale(); // falls Scale==Halbgröße, ggf. anpassen

        bool inside =
            mousePos.x >= pos.x - half.x && mousePos.x <= pos.x + half.x &&
            mousePos.y >= pos.y - half.y && mousePos.y <= pos.y + half.y;

        if (inside && pressed && !m_pressed) {
            m_pressed = true;
            if (m_onClick) m_onClick();
        } else if (!pressed) {
            m_pressed = false;
        }
    }

} // namespace pe
