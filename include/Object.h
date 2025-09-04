#pragma once
#include <vector>
class Renderer;

class Object {
public:
    virtual ~Object() = default;
    virtual void render(const Renderer& r) const = 0;

    void setPosition(std::vector<float> pos);
    void setVelocity(std::vector<float> vel);
    void setMass(float mass);

protected:
    std::vector<float> m_Position{0.f, 0.f};
    std::vector<float> m_Velocity{0.f, 0.f};
    float m_Mass{1.f};
};
