#include <Windows.h>
#include <filesystem>
#include <iostream>

#include <thread>
#include <atomic>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
//#include <glm/gtc/matrix_transform.hpp>

#include "engine/Engine.h"
#include "errors/ErrorHandler.h"

#include "buffers/VertexBuffer.h"
#include "buffers/VertexBufferLayout.h"
#include "buffers/IndexBuffer.h"
#include "buffers/VertexArray.h"
#include "shader/Shader.h"

#include "render/Drawable.h"
#include "render/Renderer.h"

#include "objects/Ball/Ball.h"
#include "objects/shapes/Circle.h"
#include "objects/shapes/Rect.h"

std::atomic<float> g_w{0.1f};
std::atomic<float> g_h{0.1f};
std::atomic<bool> g_running{true};

void readRes() {
    
    do {
        std::string in;
        std::string in2;
        std::cin >> in;
        std::cin >> in2;

        try {
            g_w.store(std::stof(in));
            g_h.store(std::stof(in2));
        } catch(std::exception &e) {
            std::cerr << "Exception caught while type convertion: " << e.what() << std::endl;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    } while(g_running.load());
}


int main() {
    // --- Essentials --- //
    Engine engine("Standart");
    ErrorHandler errorhandler;
    Renderer renderer;

    Circle circle({0.5f, 0.0f}, {0.1f, 0.2f, 0.9f, 1.0f}, 0.5f);
    Rect rect({-0.5f, 0.0f}, {0.1f, 0.8f, 0.2f, 1.0f}, {0.25f, 0.5f});
    // ---     Test Abschnitt      --- //
    

    // --- Main loop --- //
    std::thread t_read(readRes);

    while(!engine.WindowShouldClose()) {
        try {
            
            static auto last = glfwGetTime();
            auto now = glfwGetTime();
            float dt = static_cast<float>(now - last);
            last = now;
            
            
            float w = g_w.load();
            float h = g_h.load();

            rect.setSize( {w, h} );

            circle.updateVertecies();
            rect.updateVertecies();

            renderer.clearBackground({0.1f, 0.1f, 0.12f, 1.0f});
            
            renderer.clearQueue();
            renderer.addJob(&rect);
            renderer.addJob(&circle);
            renderer.processQueue();

            engine.SwapBuffersAndPollEvents();
            errorhandler.checkForErrors();
        } catch (std::exception &e) {
            std::cerr << "Exeption in the Main-Loop: " << e.what() << std::endl;
        }
    }
   
    
    engine.kill();
    return 0;
}



