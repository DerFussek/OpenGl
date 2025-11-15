#include "objects/Ball/Ball.h"
#include <iostream>

Ball::Ball(float x, float y, float r)
    : px(x), py(y), rad(r),
      shader("shaders/Ball.shader", true) {
    
    constexpr int seg = 32;
    float verts[(seg + 2) * 2];
    verts[0] = verts[1] = 0.0f;

    for(int i = 0; i <=seg; ++i) {
        float a = i * (3.141592653589793f * 2) / seg;
        verts[ (i + 1) * 2 ] = cosf(a);
        verts[ (i + 1) * 2+1] = sinf(a);
    }

    vbo = VertexBuffer(verts, sizeof(verts));
    VertexBufferLayout l; l.Push<float>(2);
    vao.AddBuffer(vbo, l);

    std::vector<unsigned int> idx(seg * 3);
    for(int i = 0; i < seg; ++i) {
        idx[ i*3 ]     = 0;
        idx[ i*3 + 1 ] = i + 1;
        idx[ i*3 + 2 ] = i + 2;
    }

    ibo = IndexBuffer(idx.data(), idx.size());
}

void Ball::draw(Renderer&) const {
    shader.Bind();
    shader.SetUniform2f("u_Pos", px, py);
    shader.SetUniform1f("u_Radius", rad);

    vao.Bind();
    ibo.Bind();

    glDrawElements(GL_TRIANGLES, ibo.getCount(), GL_UNSIGNED_INT, nullptr);
}
