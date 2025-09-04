// Renderer.h
#pragma once
class Object;
class VertexBuffer;
class VertexArray;
class Shader;

class Renderer {
public:
    void Clear();
    void DrawArray(const VertexBuffer& vb, const VertexArray& va, const Shader& shader);
    void DrawObj(const Object& obj) const; // bleibt const
};
