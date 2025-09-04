// Renderer.h
#pragma once
class Object;

class Renderer {
public:
    void Clear();
    void Draw(const Object& obj) const; // bleibt const
};
