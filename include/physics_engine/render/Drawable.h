#pragma once

#include "physics_engine/buffers/VertexBuffer.h"
#include "physics_engine/buffers/VertexBufferLayout.h"
#include "physics_engine/buffers/VertexArray.h"
#include "physics_engine/buffers/IndexBuffer.h"
#include "physics_engine/shader/Shader.h"

class Renderer;

class Drawable {
    public:
        
        virtual void draw(Renderer& r) const = 0;
        virtual ~Drawable() = default;
};