#pragma once

#include <iostream>
#include <string>
#include <array>
#include <cerrno>
#include <stdexcept>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

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
       
        
        std::array<float, 2> toPx(float x, float y);


        inline int getWidth() const { return m_Width; }
        inline int getHeight() const { return m_Height; }
};