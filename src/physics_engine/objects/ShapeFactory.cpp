#include "physics_engine/objects/ShapeFactory.h"
#include <vector>
#include <cmath>

namespace PhyEn {

std::unique_ptr<GlShape> ShapeFactory::createRect(const glm::vec2& size,
                                                  const glm::vec4& color)
{
    float hx = size.x * 0.5f;
    float hy = size.y * 0.5f;

    ShapeVertex vertices[4] = {
        {{-hx, -hy}, {0.0f, 0.0f}},
        {{ hx, -hy}, {1.0f, 0.0f}},
        {{ hx,  hy}, {1.0f, 1.0f}},
        {{-hx,  hy}, {0.0f, 1.0f}}
    };

    unsigned int indices[6] = {0,1,2, 2,3,0};

    auto shape = std::make_unique<GlShape>(vertices, 4, indices, 6, color);
    return shape;
}

std::unique_ptr<GlShape> ShapeFactory::createCircle(float radius,
                                                    int segments,
                                                    const glm::vec4& color)
{
    if (segments < 3) segments = 3;

    std::vector<ShapeVertex> vertices;
    std::vector<unsigned int> indices;

    vertices.push_back({{0.0f, 0.0f}, {0.5f, 0.5f}}); // center

    for (int i = 0; i <= segments; ++i) {
        float angle = static_cast<float>(i) / segments * 2.0f * 3.14159265f;
        float x = std::cos(angle) * radius;
        float y = std::sin(angle) * radius;
        float u = (x / (2.0f * radius)) + 0.5f;
        float v = (y / (2.0f * radius)) + 0.5f;
        vertices.push_back({{x, y}, {u, v}});
    }

    for (int i = 1; i <= segments; ++i) {
        indices.push_back(0);
        indices.push_back(i);
        indices.push_back(i + 1);
    }

    auto shape = std::make_unique<GlShape>(vertices.data(),
                                           vertices.size(),
                                           indices.data(),
                                           indices.size(),
                                           color);
    return shape;
}

} // namespace pe
