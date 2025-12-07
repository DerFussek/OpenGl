// Text.cpp
#include "physics_engine/objects/Text.h"
#include "physics_engine/render/TextRenderer.h"

Text::Text(TextRenderer& renderer,
           const std::string& content,
           const glm::vec2& position,
           float scale,
           const glm::vec3& color)
    : m_renderer(renderer),
      m_text(content),
      m_position(position),
      m_scale(scale),
      m_color(color)
{
}

void Text::render(const glm::mat4& projection)
{
    m_renderer.RenderText(
        m_text,
        m_position.x,
        m_position.y,
        m_scale,
        m_color,
        projection
    );
}

void Text::setText(const std::string& content)
{
    m_text = content;
}

void Text::setPosition(const glm::vec2& position)
{
    m_position = position;
}

void Text::setScale(float scale)
{
    m_scale = scale;
}

void Text::setColor(const glm::vec3& color)
{
    m_color = color;
}
