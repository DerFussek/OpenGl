#pragma once
#include <vector>

#include "buffers/VertexBuffer.h"
#include "buffers/VertexBufferLayout.h"
#include "buffers/IndexBuffer.h"
#include "buffers/VertexArray.h"

#include "shader/Shader.h"
#include "render/Drawable.h"

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


