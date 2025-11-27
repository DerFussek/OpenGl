#include "physics_engine/render/Drawable.h"#include "physics_engine/shader/Shader.h"


#include <iostream>
#include <vector>
#include <cmath>
#include <thread>

#include <stdexcept>
#include <cerrno>

#include <fstream>
#include <string>
#include <sstream>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

Shader::Shader(const std::string &filepath, bool CreateOnStart) 
    : m_Filepath(filepath), m_ID(0) {
    
    if(CreateOnStart) this -> Create();
}

Shader::~Shader() {
    glDeleteProgram(m_ID);
}

void Shader::Bind() const {
    glUseProgram(m_ID);
}

void Shader::Unbind() const {
    glUseProgram(0);
}

//--------------------------------------------------------------------------------------

int Shader::GetUniformLocation(const std::string &name) const {
    int location = glGetUniformLocation(m_ID, name.c_str());

    if(location == -1) {
        throw new std::runtime_error("Error in GetUniformLocation()");
        std::cerr << "Warning: uniform '" << name << "' doesn't exist!" << std::endl; 
    }

    return location;
}

void Shader::SetUniform1f(const std::string& name, float v0) const
{
    glUniform1f(GetUniformLocation(name), v0);
}

void Shader::SetUniform1i(const std::string& name, int v0) const
{
    glUniform1i(GetUniformLocation(name), v0);
}

void Shader::SetUniform1ui(const std::string& name, unsigned int v0) const
{
    glUniform1ui(GetUniformLocation(name), v0);
}

void Shader::SetUniform2f(const std::string& name, float v0, float v1) const
{
    glUniform2f(GetUniformLocation(name), v0, v1);
}

void Shader::SetUniform2i(const std::string& name, int v0, int v1) const
{
    glUniform2i(GetUniformLocation(name), v0, v1);
}

void Shader::SetUniform2ui(const std::string& name, unsigned int v0, unsigned int v1) const
{
    glUniform2ui(GetUniformLocation(name), v0, v1);
}

void Shader::SetUniform3f(const std::string& name, float v0, float v1, float v2) const
{
    glUniform3f(GetUniformLocation(name), v0, v1, v2);
}

void Shader::SetUniform3i(const std::string& name, int v0, int v1, int v2) const
{
    glUniform3i(GetUniformLocation(name), v0, v1, v2);
}

void Shader::SetUniform3ui(const std::string& name, unsigned int v0, unsigned int v1, unsigned int v2) const
{
    glUniform3ui(GetUniformLocation(name), v0, v1, v2);
}

void Shader::SetUniform4f(const std::string& name,
                          float v0, float v1, float v2, float v3) const
{
    glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
}

void Shader::SetUniform4i(const std::string& name,
                          int v0, int v1, int v2, int v3) const
{
    glUniform4i(GetUniformLocation(name), v0, v1, v2, v3);
}

void Shader::SetUniform4ui(const std::string& name,
                           unsigned int v0, unsigned int v1,
                           unsigned int v2, unsigned int v3) const
{
    glUniform4ui(GetUniformLocation(name), v0, v1, v2, v3);
}


//--------------------------------------------------------------------------------------

ShaderProgramSource Shader::ParseShader(const std::string &filepath) const {
    std::ifstream stream(filepath);

    enum class ShaderType {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];
    auto type = ShaderType::NONE; 

    try {
        while(getline(stream, line)) {
            if(line.find("#shader") != std::string::npos) {
                if(line.find("vertex") != std::string::npos) {
                    type = ShaderType::VERTEX;
                } else if(line.find("fragment") != std::string::npos) {
                    type = ShaderType::FRAGMENT;
                }
            } else {
                ss[(int)type] << line << '\n';
            }
        }
    } catch (std::exception &e) {
        throw new std::runtime_error("Error in ParseShader()");
        std::cerr << "Error: An Exception while trying to read the shaderFile has occured! (" << e.what() << ")" << std::endl;
    }

    return { ss[0].str(), ss[1].str() } ;
}

unsigned int Shader::CompileShader(unsigned int type, const std::string &source) {
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
            (std::string("Shader-Compilation failed (") + kind + "): " + (log.empty() ? "<kein log>" : log)));
        
    }

    return id;
}

unsigned int Shader::CreateShader(const std::string &vertexShader, const std::string &fragmentShader) {
    unsigned int program = glCreateProgram();
    unsigned int vs, fs;

    try {
        vs = this->CompileShader(GL_VERTEX_SHADER, vertexShader);
        fs = this->CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    } catch (std::exception &e) {
        std::cerr << "Error: An Exception has occured: " << e.what() << std::endl;
    } 

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

void Shader::Create() {
    if(m_ID != NULL) return;

    ShaderProgramSource src = ParseShader(m_Filepath);
    m_ID = CreateShader(src.VertexSource, src.FragmentSource);
    if(m_ID == NULL) throw std::runtime_error("Error in Create()");
}