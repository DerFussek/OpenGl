#include <Windows.h>
#include <filesystem>

#include "Engine/Engine.h"
#include "Renderer/Renderer.h"
#include "Objects/Circle.h"

#include "VertexBuffer/VertexBuffer.h"
#include "VertexBuffer/VertexBufferLayout.h"
#include "VertexArray/VertexArray.h"
#include "Shader/Shader.h"
#include "Objects/CircleWireFrame.h"

Engine engine("Standart");

int main() {

    Renderer renderer;
/*
    float positions[] = {
        0.5f, -0.5f,
        -0.5f, -0.5f,
        0.0f, 0.5f
    };

    VertexArray va;
    va.Bind();

    VertexBuffer buffer(positions, 6 * sizeof(float));
    VertexBufferLayout layout;
    layout.Push<float>(2);
    
    Shader shader("shaders/Basic.shader");
    shader.Bind();
    shader.SetUniform4f("u_Color", 0.0f, 0.9f, 0.9f, 1.0f);
    
    va.AddBuffer(buffer, layout);*/
    
    //Circle Circle(0.5f, 3);
    //Circle.setPosition({0.0f, 0.0f});

    CircleWireFrame Circle(0.5f, 40);
    Circle.setPosition({0.0f, 0.0f});
    Circle.setColor(0.0f, 1.0f, 0.0f);

    // --- Main loop --- //
    while(!engine.WindowShouldClose()) {
        std::cin >> Circle.m_Res;

        renderer.Clear();

        // *** Rendering *** //
        renderer.DrawObj(Circle);
        //renderer.DrawArray(buffer, va, shader);

        engine.SwapBuffersAndPollEvents();
    }

    return 0;
}
