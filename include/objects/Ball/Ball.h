#pragma once

#include "render/Drawable.h"

class Ball final : public Drawable {
    private:
        float px, py, rad;
        VertexArray  vao;
        VertexBuffer vbo;
        IndexBuffer  ibo;
        Shader       shader;
    
    public:
        Ball(float x, float y, float r);
        ~Ball() = default;
        
        void draw(Renderer& r) const override;
};