#include <Windows.h>
#include <filesystem>
#include <iostream>
#include <thread>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>


#include "engine/Engine.h"
#include "errors/ErrorHandler.h"

#include "buffers/VertexBuffer.h"
#include "buffers/VertexBufferLayout.h"
#include "buffers/IndexBuffer.h"
#include "buffers/VertexArray.h"

#include "shader/Shader.h"

int main() {
    // --- Essentials --- //
    Engine engine("Standart");
    ErrorHandler errorhandler;

    // ---           --- //
    float vertecies[] = {0.0f, 0.5f, -0.5f, -0.5f, 0.5f, -0.5f};
    VertexBuffer vbo(vertecies, 3 * 2 * sizeof(float));
    
    VertexBufferLayout layout;
    layout.Push<float>(2);

    VertexArray vao;
    
    vao.AddBuffer(vbo, layout);

    Shader shader("shaders/Basic.shader", true);
    shader.Bind();
    shader.SetUniform4f("u_Color", 0.5f, 0.2f, 0.9f, 1.0f);

    // --- Main loop --- //
    while(!engine.WindowShouldClose()) {

        shader.Bind();
        vbo.Bind();
        vao.Bind();
        
        glDrawArrays(GL_TRIANGLES, 0, vbo.getCount());
        
        
        engine.SwapBuffersAndPollEvents();
        errorhandler.checkForErrors();
    }
   
    engine.kill();
    return 0;
}



