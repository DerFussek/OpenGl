#pragma once

#include "buffers/VertexBuffer.h"
#include "buffers/VertexBufferLayout.h"
#include "buffers/IndexBuffer.h"
#include "buffers/VertexArray.h"
#include "shader/Shader.h"

class Renderer;

class Drawable {
    public:
        
        virtual void draw(Renderer& r) const = 0;
        virtual ~Drawable() = default;
};