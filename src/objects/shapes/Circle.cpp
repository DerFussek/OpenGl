#include "objects/shapes/Circle.h"

Circle::Circle(std::array<float,2>position, std::array<float,4>color, float radius)
    : shader("shaders/Shape.shader", true) {
    m_Pos = position;
    m_Color = color;
    m_Radius = radius;

    std::vector<float>vertecies;
    vertecies.reserve( (m_Res + 2) * 2);
    createVertecies(m_Radius, m_Res, vertecies);

    vb = VertexBuffer(vertecies.data(), sizeof(float) * vertecies.size());
    layout.Push<float>(2);
    va.AddBuffer(vb, layout);
    
    std::vector<unsigned int> idx(m_Res * 3);
    for(int i = 0; i < m_Res; ++i) {
        idx[ i*3 ] = 0;
        idx[ i*3 + 1 ] = i + 1;
        idx[ i*3 + 2 ] = i + 2;
    }

    ib = IndexBuffer(idx.data(), idx.size());
}

void Circle::createVertecies(float radius, int res, std::vector<float> &vertecies) {
    vertecies.clear();
    vertecies.reserve((res + 2) * 2);

    // Mittelpunkt
    vertecies.push_back(0.0f);
    vertecies.push_back(0.0f);
    
    for (int i = 0; i <= res; ++i) {
        float a = i * (3.141592653589793f * 2.0f) / res;
        vertecies.push_back(radius * cosf(a));
        vertecies.push_back(radius * sinf(a));
    }
}



void Circle::draw(Renderer&) const {
    shader.Bind();
    shader.SetUniform2f("u_Pos", m_Pos[0], m_Pos[1]);
    shader.SetUniform1f("u_Radius", m_Radius);
    shader.SetUniform4f("u_Color", m_Color[0], m_Color[1], m_Color[2], m_Color[3]);

    va.Bind();
    ib.Bind();
    
    glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, nullptr);
}

void Circle::updateVertecies() {
    std::vector<float>vertecies;
    vertecies.reserve( (m_Res + 2) * 2);
    createVertecies(m_Radius, m_Res, vertecies);

    vb.UpdateData(vertecies.data(), sizeof(float) * vertecies.size());
    //layout.Push<float>(2);
    //va.AddBuffer(vb, layout);
    
    std::vector<unsigned int> idx(m_Res * 3);
    for(int i = 0; i < m_Res; ++i) {
        idx[ i*3 ] = 0;
        idx[ i*3 + 1 ] = i + 1;
        idx[ i*3 + 2 ] = i + 2;
    }

    ib.UpdateData(idx.data(), idx.size());
}
