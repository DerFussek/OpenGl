#include <Windows.h>

#include "includes.h"
#include "Engine.h"
#include "Renderer.h"
#include "Ball.h"        // <- MUSS rein, bevor Ball benutzt wird

Engine engine("Basic");

#include <filesystem>



int main() {

    std::cout << "CWD: " << std::filesystem::current_path() << "\n";
    Ball ball(0.5f, 3);
    ball.setPosition({0.0f, 0.0f});

    Renderer renderer;

    while (!engine.WindowShouldClose()) {
        std::cin >> ball.m_Res; 

        renderer.Clear();
        renderer.Draw(ball);   // nur dieser Aufruf
        engine.SwapBuffersAndPollEvents();
    }

    engine.kill();
    return 0;
}
