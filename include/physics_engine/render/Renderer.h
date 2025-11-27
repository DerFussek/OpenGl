#pragma once
#include <vector>

#include <glad/glad.h>
#include "physics_engine/core/Engine.h"
#include "physics_engine/buffers/VertexBuffer.h"
#include "physics_engine/buffers/VertexBufferLayout.h"
#include "physics_engine/buffers/VertexArray.h"
#include "physics_engine/buffers/IndexBuffer.h"
#include "physics_engine/shader/Shader.h"
#include "physics_engine/render/Drawable.h"



struct Color {float r, g, b, a; };

class Drawable;

class Renderer {
    private:
        std::vector<const Drawable*> queue;
        

    public:
        
        static void Draw(const VertexArray &vao,
                         unsigned int vertexCount,
                         const Shader &shader);
        static void Draw(const VertexArray &vao,
                         const IndexBuffer &ib,
                         const Shader &shader);
        static void Draw(const VertexArray &vao,
                         const VertexBuffer &vbo,
                         const Shader &shader);

        template<typename T>
        void Render(T &obj) const { obj.draw(); }

        static void clearBackground(Color c);
        void clearQueue();
        void addJob(const Drawable* d);
        void processQueue();

        inline Renderer* This() { return this; }
        
};


