#include <Windows.h>
#include <filesystem>
#include <iostream>
#include <thread>

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

#include "render/Renderer.h"

#include "objects/Ball/Ball.h"

int main() {
    // --- Essentials --- //
    Engine engine("Standart");
    ErrorHandler errorhandler;
    Renderer renderer;
    Ball ball(0.0f, 0.0f, 0.1f);

    // ---     Test Abschnitt      --- //
    

    // --- Main loop --- //
    while(!engine.WindowShouldClose()) {
        try {
            
            renderer.beginFrame( {0.1f, 0.1f, 0.12f, 1.0f} );
            renderer.submit(&ball);
            renderer.endFrame();

            engine.SwapBuffersAndPollEvents();
            errorhandler.checkForErrors();
        } catch (std::exception &e) {
            std::cerr << "Exeption in the Main-Loop: " << e.what() << std::endl;
        }
        
    }
   
    engine.kill();
    return 0;
}



