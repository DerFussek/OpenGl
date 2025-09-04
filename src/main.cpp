#include <Windows.h>
#include <filesystem>

#include "Engine/Engine.h"
#include "Renderer/Renderer.h"
#include "Objects/Ball.h"

Engine engine("Standart");

int main() {

    Renderer renderer;
    
    Ball ball(0.5f, 3);
    ball.setPosition({0.0f, 0.0f});


    // --- Main loop --- //
    while(!engine.WindowShouldClose()) {
        renderer.Clear();

        // *** Rendering *** //
        renderer.DrawObj(ball);

        engine.SwapBuffersAndPollEvents();
    }

    return 0;
}
