#pragma once
#include <memory>
#include <glm/glm.hpp>
#include "physics_engine/objects/GlShape.h"
#include "physics_engine/objects/ShapeFactory.h"
#include "physics_engine/objects/Drawable.h"

namespace PhyEn {

    class Circle : public Drawable {
        private:
            std::unique_ptr<GlShape> m_shape;
        
        public:
            Circle(float radius,
                const glm::vec2& position,
                const glm::vec4& color,
                int segments = 32)
            {
                m_shape = ShapeFactory::createCircle(radius, segments, color);
                m_shape->setTransform(position, 0.0f, {1.0f, 1.0f});
            }

            void setPosition(const glm::vec2& p) {
                m_shape->setTransform(p, m_shape->rotation(), m_shape->scale());
            }

            void setRadius(float r, int segments = 32) {
                auto pos   = m_shape->position();
                auto color = m_shape->color();
                m_shape = ShapeFactory::createCircle(r, segments, color);
                m_shape->setTransform(pos, 0.0f, {1.0f, 1.0f});
            }

            void setColor(const glm::vec4& c) {
                m_shape->setColor(c);
            }

            void draw(Renderer2D& renderer) override {
                m_shape->draw(renderer);
            }    
    };

} // namespace pe
