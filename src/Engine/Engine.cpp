#include "engine/Engine.h"


Engine::Engine(const std::string windowName) {
    try {

        if(!glfwInit()) 
            throw std::runtime_error("Failed to initialize GLFW!");

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        m_Window = glfwCreateWindow(this->m_Width, this->m_Height, windowName.c_str(), nullptr, nullptr);

        if(!m_Window) {
            kill();
            throw std::runtime_error("Failed to create GLFW window!");
        }

        glfwMakeContextCurrent(m_Window);

        if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) 
            throw std::runtime_error("Failed to initialize Glad!");

        glViewport(0, 0, m_Width, m_Height);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    } catch (std::exception& e) {
        std::cerr << "Error: Caught Expression: " << e.what() << std::endl;
        _ASSERT("Caught Expression while starting up!");
    }
}

Engine::~Engine() {
    glfwTerminate();
}

void Engine::SwapBuffersAndPollEvents() {
    glfwSwapBuffers(this->m_Window);
    glfwPollEvents();
}

void Engine::kill()
{
    glfwTerminate();
}

bool Engine::WindowShouldClose() {
    return glfwWindowShouldClose(this->m_Window);
}
