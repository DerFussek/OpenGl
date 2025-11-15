#include "engine/Engine.h"
#include "render/Renderer.h"
#include <glad/glad.h>
#include "buffers/VertexArray.h"
#include "buffers/IndexBuffer.h"
#include "shader/Shader.h"
#include <vector>
#include <thread>
#include <atomic>
#include <mutex>
#include <iostream>
#include <exception>   // std::exception
#include <algorithm>   // std::max


void Renderer::clearBackground(Color c) {
    glClearColor(c.r, c.g, c.b, c.a);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::Draw(const VertexArray &vao,
                    unsigned int vertexCount,
                    const Shader &shader) {
    shader.Bind();
    vao.Bind();
    glDrawArrays(GL_TRIANGLES, 0, vertexCount);
}

void Renderer::Draw(const VertexArray &vao,
                    const IndexBuffer &ib,
                    const Shader &shader) {

    shader.Bind();
    vao.Bind();
    ib.Bind();

    glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::Draw(const VertexArray &vao,
                    const VertexBuffer &vbo,
                    const Shader &shader)  {
    shader.Bind();
    vbo.Bind();
    vao.Bind();

    glDrawArrays(GL_TRIANGLES, 0, vbo.getCount());
}

void Renderer::clearQueue() {
    queue.clear();
    
}

void Renderer::addJob(const Drawable* d) { queue.push_back(d); }
void Renderer::processQueue() {
    try { 
        for (auto* d : queue) d ->draw(*this); 
    } catch (std::exception &e) { 
        std::cerr << "Exception during queue processing: " << e.what() << std::endl; 
    } 
}


