// Text.h
#pragma once

#include <string>
#include <glm/glm.hpp>
#include "physics_engine/render/TextRenderer.h"

class Text
{
    private:
        TextRenderer& m_renderer;

        std::string m_text;
        glm::vec2   m_position;
        float       m_scale;
        glm::vec3   m_color;

    public:
        Text(TextRenderer& renderer,
            const std::string& content,
            const glm::vec2& position,
            float scale,
            const glm::vec3& color);

        void render(const glm::mat4& projection);

        // Setter
        void setText(const std::string& content);
        void setPosition(const glm::vec2& position);
        void setScale(float scale);
        void setColor(const glm::vec3& color);

        // Getter optional
        const std::string& getText() const { return m_text; }
        const glm::vec2& getPosition() const { return m_position; }
        float getScale() const { return m_scale; }
        const glm::vec3& getColor() const { return m_color; }
};
