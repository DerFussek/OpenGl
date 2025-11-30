// ## OS ## 
#include <Windows.h>
//#include <filesystem>
#include <iostream>
#include <sstream>      // <-- fehlt bei dir

// ## Threading ##
#include <thread>
#include <atomic>

// ## External Libs ##
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// ## Engine ##
#include "physics_engine/core/Engine.h"          // Pfad an deine Struktur anpassen
#include "physics_engine/error/ErrorHandler.h"
#include "physics_engine/objects/ObjectManager.h"
#include "physics_engine/objects/shapes/GlCircle.h"
#include "physics_engine/objects/shapes/GlRect.h"

#include "physics_engine/buffers/VertexBuffer.h"
#include "physics_engine/buffers/VertexBufferLayout.h"
#include "physics_engine/buffers/VertexArray.h"
#include "physics_engine/buffers/IndexBuffer.h"
#include "physics_engine/shader/Shader.h"
#include "physics_engine/render/Renderer.h"
#include "physics_engine/objects/ObjectBase.h"

// ## UI ##
#include "physics_engine/ui/Panel.h"
#include "physics_engine/ui/Button.h"


// ## Global Vars and Functions ##
std::atomic<float> g_w{0.1f};       // Test vars for
std::atomic<float> g_h{0.1f};       // for threaded 
std::atomic<bool> g_running{true};  // user imput

#define ReadThreadSleepTime 10
void readResWin() {
    HANDLE event = GetStdHandle(STD_INPUT_HANDLE);
    if(event == INVALID_HANDLE_VALUE) return;

    std::string buffer;
    std::cout << "> " << std::flush;

    while(g_running.load()) {
        DWORD numEvents = 0;

        if(!GetNumberOfConsoleInputEvents(event, &numEvents)) { // Fehler 
            std::this_thread::sleep_for(std::chrono::milliseconds(ReadThreadSleepTime));
            continue;
        }

        if(numEvents == 0) {    // keine Events
            std::this_thread::sleep_for(std::chrono::milliseconds(ReadThreadSleepTime));
            continue;
        }

        INPUT_RECORD rec;
        DWORD read = 0;
        if(!ReadConsoleInputA(event, &rec, 1, &read) || read == 0) continue;
        if(rec.EventType != KEY_EVENT) continue;

        KEY_EVENT_RECORD& key = rec.Event.KeyEvent;
        if(!key.bKeyDown) continue;
        char ch = key.uChar.AsciiChar;

        if(ch == '\r') {
            std::cout << '\n';

            try {
                std::istringstream iss(buffer);
                float w, h;

                if(iss >> w >> h) {
                    g_w.store(w);
                    g_h.store(h);
                    std::cout << "Neue Wete: w=" << w << " h=" << h << "\n";
                } else {
                    std::cout << "Eingabe-Format: <w> <h>\n";
                }
            } catch(std::exception &e) {
                std::cerr << "Parse-Fehler: " << e.what() << "\n";
            }

            buffer.clear();
            std::cout << "> " << std::flush;
        } else if(ch == '\b') {
            if(!buffer.empty()) buffer.pop_back();
        } else if(ch >= 32 && ch < 127) {
            buffer.push_back(ch);
            std::cout << ch << std::flush;
        }
    }
}


// ## Main Function ## 
int main() {
    // -- UI -- //
    Panel inspector;
    Panel scene;
    InputState gInput;

    // --- Essentials --- //
    Engine engine("Standart");
    ErrorHandler errorhandler;
    Renderer renderer;
    ObjectManager manager;

    while(!engine.WindowShouldClose()) {
        try {
            static auto last = glfwGetTime();
            auto now = glfwGetTime();
            float dt = static_cast<float>(now - last);
            last = now;

            engine.UpdateInput(gInput);

            int winW, winH;
            engine.getFrameBufferSize(&winW, &winH);
            inspector.rect = {0.0f, 0.0f, winW * 0.3f, (float)winH};
            scene.rect = {winW * 0.3f, 0.0f, winW * 0.7f, (float)winH};

            ButtonState btnSimulate;
            Rect btnRect {
                inspector.rect.x + 10.0f,
                inspector.rect.y + 10.0f,
                inspector.rect.w - 20.0f,
                30.0f
            };

            bool startSim = DoButton("StartSimulation", btnRect, gInput, btnSimulate);
            if (startSim) {
                
            }


            engine.SwapBuffersAndPollEvents();
            errorhandler.checkForErrors();
        } catch (std::exception &e) {
            std::cerr << "Exeption in the Main-Loop: " << e.what() << std::endl;
        }
    }
    
    engine.kill();
    return 0;
}



