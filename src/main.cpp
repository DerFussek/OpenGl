#include <Windows.h>

#include <iostream>
#include <vector>
#include <cmath>
#include <stdexcept>
#include <fstream>
#include <string>
#include <sstream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

struct Engine {
    GLFWwindow* window;
    int WIDTH = 800;
    int HEIGHT = 600;

    Engine() {
        if(!glfwInit()) throw("glfwInit failed!\n");

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
        
        window = glfwCreateWindow(WIDTH, HEIGHT, "Standart Engine", nullptr, nullptr);
        if(!window) {
            glfwTerminate();
            throw("Failed to create GLFW window!\n");
            exit(EXIT_FAILURE);
        }
        glfwMakeContextCurrent(window);

        if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            throw("Faild to initialize Glad!\n");
            exit(EXIT_FAILURE);
        }
    }

    void kill() {
        glfwTerminate();
    }

    void run() {
       glClear(GL_COLOR_BUFFER_BIT); 
    }

    struct ShaderProgramSource {
        std::string VertexSource;
        std::string FragmentSource;
    };

    ShaderProgramSource ParseShader(const std::string& filePath) {
        std::ifstream stream(filePath);

        enum class ShaderType {
            NONE = -1, VERTEX = 0, FRAGMENT = 1
        };

        std::string line;
        std::stringstream ss[2];
        ShaderType type = ShaderType::NONE;
        while(getline(stream, line)) {
            if(line.find("#shader") != std::string::npos) {
                if(line.find("vertex") != std::string::npos) {
                    type = ShaderType::VERTEX;
                } else if (line.find("fragment") != std::string::npos) {
                    type = ShaderType::FRAGMENT;
                }
            } else {
                ss[(int)type] << line << '\n';
            }
        }

        return {ss[0].str(), ss[1].str()};
    }

    unsigned int CompileShader(unsigned int type, const std::string& source) {
        unsigned int id = glCreateShader(type);
        const char* src = source.c_str();
        glShaderSource(id, 1, &src, nullptr);
        glCompileShader(id);

        int res;
        glGetShaderiv(id, GL_COMPILE_STATUS, &res);
        if(res == GL_FALSE) {
            int len;
            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &len);
            char* msg = (char*)alloca(len * sizeof(char));
        
            glGetShaderInfoLog(id, len, &len, msg);
            glDeleteShader(id);
            return 0;
            //throw std::logic_error(msg);
        }


        return id;
    }

    unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader) {
        unsigned int program = glCreateProgram();
        unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
        unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

        glAttachShader(program, vs);
        glAttachShader(program, fs);
        glLinkProgram(program);
        glValidateProgram(program);

        glDeleteShader(vs);
        glDeleteShader(fs);

        return program;
    }
};

Engine engine;


// ---   Main function   --- //
int main() {

    float positions[6] {
        -0.5f, -0.5f,
        0.0f, 0.5f,
        0.5f, -0.5f
    };

    unsigned int buffer_ID;
    glGenBuffers(1, &buffer_ID); // Buffer erstellen und ID in buffer_ID speichern
    glBindBuffer(GL_ARRAY_BUFFER, buffer_ID); // Select Bufffer (select == bind)
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0); //OpenGL sagen welcher datentyp im Buffer ist und wie er aufgebaut ist

    Engine::ShaderProgramSource source = engine.ParseShader("shaders/Basic.shader");

    std::cout << source.VertexSource << '\n';
    std::cout << source.FragmentSource << '\n';

    unsigned int shader = engine.CreateShader(source.VertexSource, source.FragmentSource);
    glUseProgram(shader);

    while(!glfwWindowShouldClose(engine.window)) {
        engine.run();

        glDrawArrays(GL_TRIANGLES, 0, 3);
        

        glfwSwapBuffers(engine.window);
        glfwPollEvents();
    }

    glDeleteProgram(shader);
    engine.kill();
    return 0;
}