// Circle.cpp
#include "Objects/Circle.h"
#include "Renderer/Renderer.h"
#include "VertexBuffer/VertexBufferLayout.h"
#include <cmath>

Circle::Circle(float radius, int res)
    : m_Res(res), m_Radius(radius), m_shader("shaders/Basic.shader", true) {}

void Circle::ensureReady() const {
    if (m_ready) return;
    m_va.Bind();
    VertexBufferLayout layout;
    layout.Push<float>(2);           // vec2 Position
    m_va.AddBuffer(m_vb, layout);    // Attribute setzen
    m_ready = true;
}

std::vector<float> Circle::createPositionVertices() const {
    if (m_Res < 2 || m_Radius <= 0.f) return {};

    std::vector<float> v; 
    v.reserve((m_Res+2)*2);

    // center
    v.push_back(m_Position[0]);
    v.push_back(m_Position[1]);

    const float twoPi = 6.283185307179586f;
    for (int i=0; i<=m_Res; ++i) {
        float t = twoPi * (float(i) / float(m_Res));
        v.push_back(m_Position[0] + std::cos(t) * m_Radius);
        v.push_back(m_Position[1] + std::sin(t) * m_Radius);
    }


    // --- Debug Ausgabe ---
    /*
    std::cout << "Circle vertices (" << v.size()/2 << " Punkte): ";
    for (size_t i = 0; i < v.size(); i+=2) {
        std::cout << "(" << v[i] << ", " << v[i+1] << ") ";
    }
    std::cout << std::endl;
    */
    // ----------------------

    return v;
}


void Circle::render(const Renderer&) const {
    ensureReady();
    auto data = createPositionVertices();
    if (data.empty()) return;

    m_vb.ChangeData(data.data(),
                    static_cast<unsigned int>(data.size()*sizeof(float)));
    m_vertexCount = static_cast<unsigned int>(data.size()/2); // 2 floats/Vertex

    m_shader.Bind();
    m_va.Bind();
    m_shader.SetUniform4f("u_Color", m_Color[0], m_Color[1], m_Color[2], m_Color[3]);

    glDrawArrays(GL_TRIANGLE_FAN, 0, static_cast<GLsizei>(m_vertexCount));
}
