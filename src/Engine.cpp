#include "Engine.h"

Engine::Engine(const std::string windowName)
{
    try  {
        if(!glfwInit()) throw std::runtime_error("Failed to initialize GLFW!");
        
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        
        window = glfwCreateWindow(this->m_Width, this->m_Height, windowName.c_str(), nullptr, nullptr);
        
        if(!window) {
            glfwTerminate();
            throw std::runtime_error("Failed to create GLFW window!");
        }

        glfwMakeContextCurrent(window);

        if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
                throw std::runtime_error("Failed to initialize Glad!");
        }

        glViewport(0, 0, m_Width, m_Height);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);


    } catch (std::exception& e) {
        std::cerr << "Error: Caught Expression: " << e.what() << std::endl;
    }
}

Engine::~Engine()
{
    glfwTerminate();
}

bool Engine::WindowShouldClose()
{
    return glfwWindowShouldClose(this->window);
}

void Engine::SwapBuffersAndPollEvents()
{
    glfwSwapBuffers(this->window);
    glfwPollEvents();
}

void Engine::kill()
{
    glfwTerminate();
}
