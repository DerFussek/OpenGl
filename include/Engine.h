#pragma once
#include <iostream>
#include <vector>
#include <cmath>

#include <stdexcept>
#include <cerrno>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Shader.h"
#include "Renderer.h"


class Engine {
    private:
        int m_Width = 800;
        int m_Height = 800;
        GLFWwindow* window;

    public: 
        Engine(const std::string windowName);
        ~Engine();

        bool WindowShouldClose();
        void SwapBuffersAndPollEvents();

        void kill();

};