#pragma once

#include <iostream>
#include <string>
#include <array>
#include <cerrno>
#include <stdexcept>

#include <glad/glad.h>
#include <GLFW/glfw3.h>


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
        
        std::array<float, 2> toPx(float x, float y);
        

        inline int getWidth() const { return m_Width; }
        inline int getHeight() const { return m_Height; }
        inline void getFrameBufferSize(int *w, int *h) const { glfwGetFramebufferSize(m_Window, w, h); }
};