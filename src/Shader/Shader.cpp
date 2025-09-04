#include "Shader/Shader.h"

#include <iostream>
#include <vector>
#include <cmath>

#include <stdexcept>
#include <cerrno>

#include <fstream>
#include <string>
#include <sstream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

Shader::Shader(const std::string &filepath, bool CreateOnStart)
    : m_FilePath(filepath), m_RendererID(0)
{
    if(CreateOnStart) this->Create();
}

Shader::~Shader()
{
        glDeleteProgram(m_RendererID);
}

// ---------------------------------------------------------------------------------------------------------

void Shader::Bind() const {
    glUseProgram(m_RendererID);
}

void Shader::Unbind() const {
    glUseProgram(0);
}

// ---------------------------------------------------------------------------------------------------------

// Shader.cpp (nur Signaturen anpassen)
void Shader::SetUniform4f(const std::string &name, float v0, float v1, float v2, float v3) const {
    glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
}

int Shader::GetUniformLocation(const std::string &name) const {
    int location = glGetUniformLocation(m_RendererID, name.c_str());
    if (location == -1) {
        std::cout << "Warning: uniform '" << name << "' doesn't exist!" << std::endl;
    }
    return location;
}


// ---------------------------------------------------------------------------------------------------------

 ShaderProgramSource Shader::ParseShader(const std::string& filepath) const {
        std::ifstream stream(filepath);

        enum class ShaderType {
            NONE = -1, VERTEX = 0, FRAGMENT = 1
        };

        std::string line;
        std::stringstream ss[2];
        ShaderType type = ShaderType::NONE;
        
        try {
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
        } catch (std::exception& e) {
            std::cerr << "Error: An Exception while trying to read the shaderFile has occured! (" << e.what() << ")" << std::endl;
            _ASSERT("Shader::ParseShader");
        }

        return {ss[0].str(), ss[1].str()};
    }


unsigned int Shader::CreateShader(const std::string &vertexShader, const std::string &fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs;
    unsigned int fs;

    try {
        vs = this->CompileShader(GL_VERTEX_SHADER, vertexShader);
        fs = this->CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
    } catch (std::exception& e) {
        std::cerr << "Error: An Exception has occured: " << e.what() << std::endl;
        _ASSERT("Shader::CreateShader");
    };
    
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);
    
    return program;
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source) {
        unsigned int id = glCreateShader(type);
        const char* src = source.c_str();

        glShaderSource(id, 1, &src, nullptr);
        glCompileShader(id);

        int ok = GL_FALSE;
        glGetShaderiv(id, GL_COMPILE_STATUS, &ok);

        if(!ok) {
            int len = 0;
            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &len);

            std::string log;
            if(len > 1) {
                std::vector<char> buf(static_cast<size_t>(len));
                glGetShaderInfoLog(id, len, nullptr, buf.data());
                log.assign(buf.data());
            }

            glDeleteShader(id);

            const char* kind;
            if(type == GL_VERTEX_SHADER) kind = "Vertex";
            else if(type == GL_FRAGMENT_SHADER) kind = "Fragment";
            else kind = "Unknown";
            
            throw std::runtime_error(
                (std::string("Shader-Compilation failed (") + kind + "): " +
                (log.empty() ? "<kein log>" : log))
            );
                
        }

        return id;
}

// ---------------------------------------------------------------------------------------------------------

void Shader::Create() {
    if(m_RendererID != NULL) return;
    
    ShaderProgramSource source = ParseShader(m_FilePath);
    m_RendererID = CreateShader(source.VertexSource, source.FragmentSource);
}