// ## OS ## 
#include <Windows.h>
//#include <filesystem>
#include <iostream>
#include <sstream>     

// ## Threading ##
#include <thread>
#include <atomic>

// ## External Libs ##
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// ## Engine ##
#include "physics_engine/core/Engine.h"          
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

// ## Main Function ## 
int main() {
    
    // --- Essentials --- //
    Engine engine("Standart");
    ErrorHandler errorhandler;
    Renderer renderer;
    ObjectManager manager;

        // -- UI -- //
    Panel inspector{};
    Panel scene{};
    GlRect* btnRectShape = nullptr;
    InputState gInput{};

    while (!engine.WindowShouldClose()) {
        try {
            static auto last = glfwGetTime();
            auto now = glfwGetTime();
            float dt = static_cast<float>(now - last);
            last = now;

            engine.UpdateInput(gInput);
            
            int winW, winH;
            engine.getFrameBufferSize(&winW, &winH);
            glViewport(0, 0, winW, winH);

            // ===================== INSPECTOR (links) =====================
            inspector.screenRect = {
                0.0f,
                0.0f,
                winW * 0.3f,
                (float)winH
            };

            float inspCenterX_px = inspector.screenRect.x + inspector.screenRect.w * 0.5f;
            float inspCenterY_px = inspector.screenRect.y + inspector.screenRect.h * 0.5f;

            float inspCenterX_ndc = Engine::PixelToNdcX(inspCenterX_px, winW);
            float inspCenterY_ndc = Engine::PixelToNdcY(inspCenterY_px, winH);

            float inspWidth_ndc  = (inspector.screenRect.w / winW) * 2.0f;
            float inspHeight_ndc = (inspector.screenRect.h / winH) * 2.0f;

            std::array<float, 4> inspColor = {0.2f, 0.2f, 0.2f, 1.0f};

            if (!inspector.rect) {
                inspector.rect = manager.CreateRect(
                    inspCenterX_ndc, inspCenterY_ndc,
                    inspColor,
                    inspWidth_ndc, inspHeight_ndc
                );
            } else {
                inspector.rect->setPosition(inspCenterX_ndc, inspCenterY_ndc);
                inspector.rect->setSize(inspWidth_ndc, inspHeight_ndc);
            }

            // ===================== SCENE (rechts) =====================
            scene.screenRect = {
                winW * 0.3f,      // Start rechts vom Inspector
                0.0f,
                winW * 0.7f,
                (float)winH
            };

            float sceneCenterX_px = scene.screenRect.x + scene.screenRect.w * 0.5f;
            float sceneCenterY_px = scene.screenRect.y + scene.screenRect.h * 0.5f;

            float sceneCenterX_ndc = Engine::PixelToNdcX(sceneCenterX_px, winW);
            float sceneCenterY_ndc = Engine::PixelToNdcY(sceneCenterY_px, winH);

            float sceneWidth_ndc  = (scene.screenRect.w / winW) * 2.0f;
            float sceneHeight_ndc = (scene.screenRect.h / winH) * 2.0f;

            std::array<float, 4> sceneColor = {0.1f, 0.1f, 0.1f, 1.0f};

            if (!scene.rect) {
                scene.rect = manager.CreateRect(
                    sceneCenterX_ndc, sceneCenterY_ndc,
                    sceneColor,
                    sceneWidth_ndc, sceneHeight_ndc
                );
            } else {
                scene.rect->setPosition(sceneCenterX_ndc, sceneCenterY_ndc);
                scene.rect->setSize(sceneWidth_ndc, sceneHeight_ndc);
            }

            // ===================== BUTTON im INSPECTOR =====================
            ButtonState btnSimulate;
            Rect btnRect{
                inspector.screenRect.x + 10.0f,
                inspector.screenRect.y + 10.0f,
                inspector.screenRect.w - 20.0f,
                30.0f
            };

            bool startSim = DoButton("StartSimulation", btnRect, gInput, btnSimulate);
            if (startSim) {
                // TODO: Simulations-Flag setzen
                std::cout << "CLICK!\n";
            }

            // Button als GlRect zeichnen (NDC)
            float btnCenterX_px = btnRect.x + btnRect.w * 0.5f;
            float btnCenterY_px = btnRect.y + btnRect.h * 0.5f;

            float btnCenterX_ndc = Engine::PixelToNdcX(btnCenterX_px, winW);
            float btnCenterY_ndc = Engine::PixelToNdcY(btnCenterY_px, winH);

            float btnWidth_ndc  = (btnRect.w / winW) * 2.0f;
            float btnHeight_ndc = (btnRect.h / winH) * 2.0f;

            // Farbe je nach Zustand
            std::array<float, 4> btnColor;
            if (btnSimulate.pressed) {
                btnColor = {0.25f, 0.25f, 0.35f, 1.0f}; // pressed
            } else if (btnSimulate.hovered) {
                btnColor = {0.20f, 0.20f, 0.30f, 1.0f}; // hover
            } else {
                btnColor = {0.15f, 0.15f, 0.25f, 1.0f}; // normal
            }

            if (!btnRectShape) {
                btnRectShape = manager.CreateRect(
                    btnCenterX_ndc, btnCenterY_ndc,
                    btnColor,
                    btnWidth_ndc, btnHeight_ndc
                );
            } else {
                btnRectShape->setPosition(btnCenterX_ndc, btnCenterY_ndc);
                btnRectShape->setSize(btnWidth_ndc, btnHeight_ndc);
                btnRectShape->setColor(btnColor);
            }

            // ===================== RENDERING =====================

            renderer.addJob(inspector.rect);
            renderer.addJob(scene.rect);
            if(btnRectShape) renderer.addJob(btnRectShape);

            for(auto& [id, ptr] : manager.GetAllRects()) {
                GlRect* obj = ptr.get();
                renderer.addJob(obj);
            }

            for(auto& [id, ptr] : manager.GetAllCircles()) {
                GlCircle* obj = ptr.get();
                renderer.addJob(obj);
            }

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



