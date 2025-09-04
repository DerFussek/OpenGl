#include "Object/Object.h"

void Object::setPosition(std::vector<float> pos) { m_Position = std::move(pos); }
void Object::setVelocity(std::vector<float> vel) { m_Velocity = std::move(vel); }
void Object::setMass(float mass) { if (mass >= 0.f) m_Mass = mass; }
