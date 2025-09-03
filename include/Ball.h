// Ball.h
#pragma once
#include "Object.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "Shader.h"
#include <array>
#include <vector>

class Renderer; // forward

class Ball : public Object {
public:
    Ball(float radius, int res);
    void render(const Renderer& r) const override; // exakt so!

    void setColor(float r,float g,float b,float a=1.0f){ m_Color={r,g,b,a}; }

public:
    void ensureReady() const;
    std::vector<float> createPositionVertices() const;

    mutable bool         m_ready = false;
    mutable VertexArray  m_va;
    mutable VertexBuffer m_vb;
    mutable unsigned int m_vertexCount = 0;

    int    m_Res;
    float  m_Radius;
    Shader m_shader;
    std::array<float,4> m_Color{0,0,1,1};
};
