#include "physics_engine/ui/UIElement.h"

namespace PhyEn {

    UIElement::UIElement(const glm::vec2& position,
                        const glm::vec2& size,
                        const glm::vec4& color)
    {
        m_shape = ShapeFactory::createRect(size, color);
        m_shape->setTransform(position, 0.0f, {1.0f, 1.0f});
    }

    void UIElement::setPosition(const glm::vec2& pos)
    {
        m_shape->setTransform(pos, 0.0f, m_shape->scale());
    }

    void UIElement::setSize(const glm::vec2& size)
    {
        glm::vec2 scale = size; // hier nach Bedarf anpassen
        m_shape->setTransform(m_shape->position(), 0.0f, scale);
    }

    void UIElement::setColor(const glm::vec4& color)
    {
        m_shape->setColor(color);
    }

    void UIElement::draw(Renderer2D& renderer)
    {
        m_shape->draw(renderer);
    }

} // namespace pe
