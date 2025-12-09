#pragma once

#include <iostream>
#include <string>
#include <array>
#include <cerrno>
#include <stdexcept>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace PhyEn {

    struct InputState {
        double mouseX, mouseY;
        bool mouseDownLeft;
        bool mousePressedLeft;
    };

    class Engine {
        public:
            int m_Width = 800;
            int m_Height = 800;
            GLFWwindow* m_Window;
        
        public:
            Engine(const std::string windowName);
            ~Engine();

            bool WindowShouldClose();
            void SwapBuffersAndPollEvents();
            void kill();

            void UpdateInput(InputState& in) {
                glfwGetCursorPos(m_Window, &in.mouseX, &in.mouseY);
                int state = glfwGetMouseButton(m_Window, GLFW_MOUSE_BUTTON_LEFT);
                static bool lastDown = false;
                in.mouseDownLeft = (state == GLFW_PRESS);
                in.mousePressedLeft = (!lastDown && in.mouseDownLeft);
                lastDown = in.mouseDownLeft;
            }

            static float PixelToNdcX(float x, int winW) {
                return (x / (float)winW) * 2.0f - 1.0f;
            }

            static float PixelToNdcY(float y, int winH) {
                // Pixel-Y: oben = 0, unten = winH
                // NDC-Y : unten = -1, oben = +1
                return 1.0f - (y / (float)winH) * 2.0f;
            }

            static float NdcToPixelX(float x, int winW) {
                return (x + 1.0f) * 0.5f * (float)winW;
            }

            static float NdcToPixelY(float y, int winH) {
                return (1.0f - y) * 0.5f * (float)winH;
            }

            void updateDimensions() {
                glfwGetFramebufferSize(m_Window, &m_Width, &m_Height);
            }

            std::array<float, 2> toPx(float x, float y);
            

            inline int getWidth() const { return m_Width; }
            inline int getHeight() const { return m_Height; }
            inline void getFrameBufferSize(int *w, int *h) const { glfwGetFramebufferSize(m_Window, w, h); }
    };

}