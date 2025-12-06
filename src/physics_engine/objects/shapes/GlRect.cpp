#include "physics_engine/objects/shapes/GlRect.h"
#include "physics_engine/render/Drawable.h"

GlRect::GlRect()
    : shader("../../assets/shaders/Shape.shader", true),
      ObjectBase("GlRect_Default")
{
    std::vector<float> vertecies = createVertecies(m_Width, m_Height);
    vb = VertexBuffer(vertecies.data(), sizeof(float) * vertecies.size());
    layout.Push<float>(2);
    va.AddBuffer(vb, layout);
}

GlRect::GlRect(const std::string& id,
               float posX, float posY,
               const std::array<float, 4>& color,
               float width, float height)
    : shader("../../assets/shaders/Rect.shader", true),
      ObjectBase(id)
{
    m_PosX = posX;
    m_PosY = posY;
    m_Color = color;
    m_Width  = width;
    m_Height = height;

    std::vector<float> vertecies = createVertecies(m_Width, m_Height);
    vb = VertexBuffer(vertecies.data(), sizeof(float) * vertecies.size());
    layout.Push<float>(2);
    va.AddBuffer(vb, layout);
}

std::vector<float> GlRect::createVertecies(float width, float height) const {
    const float halfW = width  * 0.5f;
    const float halfH = height * 0.5f;

    std::vector<float> verts;
    verts.reserve(6 * 2);

    // Dreieck 1
    verts.push_back(-halfW); verts.push_back(-halfH);
    verts.push_back( halfW); verts.push_back(-halfH);
    verts.push_back( halfW); verts.push_back( halfH);

    // Dreieck 2
    verts.push_back(-halfW); verts.push_back(-halfH);
    verts.push_back( halfW); verts.push_back( halfH);
    verts.push_back(-halfW); verts.push_back( halfH);

    return verts;
}

void GlRect::draw(Renderer& r) const {
    shader.Bind();
    shader.SetUniform2f("u_Pos",   m_PosX, m_PosY);
    shader.SetUniform4f("u_Color", m_Color[0], m_Color[1], m_Color[2], m_Color[3]);

    vb.Bind();
    va.Bind();

    glDrawArrays(GL_TRIANGLES, 0, vb.getCount());
}

void GlRect::updateVertecies() {
    std::vector<float> vertecies = createVertecies(m_Width, m_Height);
    vb.UpdateData(vertecies.data(), sizeof(float) * vertecies.size());
}

bool GlRect::contains(float x, float y) const {
    const float halfW = m_Width  * 0.5f;
    const float halfH = m_Height * 0.5f;

    const float left   = m_PosX - halfW;
    const float right  = m_PosX + halfW;
    const float bottom = m_PosY - halfH;
    const float top    = m_PosY + halfH;

    return (x >= left && x <= right &&
            y >= bottom && y <= top);
}
