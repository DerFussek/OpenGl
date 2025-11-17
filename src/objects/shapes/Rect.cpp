#include "objects/shapes/Rect.h"

Rect::Rect(std::array<float, 2>pos, std::array<float, 4>color, std::array<float, 2>size) 
    : shader("shaders/Basic.shader", true) {
    
    m_Pos = pos;
    m_Color = color;
    m_Size = size;

    std::vector<float> vertecies = createVertecies(m_Size);
    vb = VertexBuffer(vertecies.data(), sizeof(float) * vertecies.size());
    layout.Push<float>(2);
    va.AddBuffer(vb, layout);
}

std::vector<float> Rect::createVertecies(std::array<float, 2>size) {
    const float halfW = size[0] * 0.5f;
    const float halfH = size[1] * 0.5f;
    
    std::vector<float> verts;
    verts.reserve( 6 * 2 );

    //Rectangle 1
    verts.push_back( -halfW );  verts.push_back( -halfH ); // lower left
    verts.push_back( halfW );   verts.push_back( -halfH);  // lower right
    verts.push_back( halfW );   verts.push_back( halfH );  // upper right

    //Rectangle 2
    verts.push_back( -halfW );  verts.push_back( -halfH ); // lower left
    verts.push_back( halfW );   verts.push_back( halfH );  // upper right
    verts.push_back( -halfW );  verts.push_back( halfH );  // upper left

    return verts;
}

void Rect::draw(Renderer& r) const {
    shader.Bind();
    shader.SetUniform2f("u_Pos", m_Pos[0], m_Pos[1]);
    shader.SetUniform4f("u_Color", m_Color[0], m_Color[1], m_Color[2], m_Color[3]);

    vb.Bind();
    va.Bind();

    glDrawArrays(GL_TRIANGLES, 0, vb.getCount());
}

void Rect::updateVertecies() {
    std::vector<float> vertecies = createVertecies(m_Size);
    vb.UpdateData(vertecies.data(), sizeof(float) * vertecies.size());
}