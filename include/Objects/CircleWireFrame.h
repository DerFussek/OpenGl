#pragma once
#include "Object/Object.h"
#include "VertexArray/VertexArray.h"
#include "VertexBuffer/VertexBuffer.h"
#include "VertexBuffer/VertexBufferLayout.h"
#include "Shader/Shader.h"
#include <vector>
#include <cmath>
#include <array>

class Renderer;

class CircleWireFrame : public Object {
public:
    CircleWireFrame(float radius, int res)
        : m_Res(res), m_Radius(radius), m_shader("shaders/Basic.shader", true) {}

    void render(const Renderer& r) const override {
        ensureReady();
        auto data = createPositionVertices();
        if (data.empty()) return;

        m_vb.ChangeData(data.data(), static_cast<unsigned int>(data.size() * sizeof(float)));
        m_vertexCount = static_cast<unsigned int>(data.size() / 2);

        m_shader.Bind();
        m_va.Bind();
        m_shader.SetUniform4f("u_Color", m_Color[0], m_Color[1], m_Color[2], m_Color[3]);

        // Wireframe-Modus
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glDrawArrays(GL_TRIANGLE_FAN, 0, static_cast<GLsizei>(m_vertexCount));
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // zurücksetzen
    }

    void setColor(float r,float g,float b,float a=1.0f){ m_Color={r,g,b,a}; }

public:
    void ensureReady() const {
        if (m_ready) return;
        m_va.Bind();
        VertexBufferLayout layout;
        layout.Push<float>(2); // vec2 Position
        m_va.AddBuffer(m_vb, layout);
        m_ready = true;
    }

    std::vector<float> createPositionVertices() const {
        if (m_Res < 2 || m_Radius <= 0.f) return {};
        std::vector<float> v;
        v.reserve((m_Res+2)*2);

        // Zentrum
        v.push_back(m_Position[0]);
        v.push_back(m_Position[1]);

        const float twoPi = 6.283185307179586f;
        for (int i = 0; i <= m_Res; ++i) {
            float t = twoPi * (float(i)/float(m_Res));
            v.push_back(m_Position[0] + std::cos(t)*m_Radius);
            v.push_back(m_Position[1] + std::sin(t)*m_Radius);
        }
        return v;
    }

    mutable bool         m_ready = false;
    mutable VertexArray  m_va;
    mutable VertexBuffer m_vb;
    mutable unsigned int m_vertexCount = 0;

    int    m_Res;
    float  m_Radius;
    Shader m_shader;
    std::array<float,4> m_Color{1.f,1.f,1.f,1.f};
};
