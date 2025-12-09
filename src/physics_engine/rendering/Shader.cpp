#include "physics_engine/rendering/Shader.h"
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include <fstream>
#include <sstream>
#include <iostream>

namespace PhyEn {

std::string Shader::loadFile(const std::string& path)
{
    std::ifstream file(path, std::ios::in);
    if (!file.is_open()) {
        std::cerr << "Failed to open shader file: " << path << std::endl;
        return "";
    }

    std::stringstream ss;
    ss << file.rdbuf();
    return ss.str();
}

Shader::Shader(const std::string& vertexPath,
               const std::string& fragmentPath)
{
    std::string vertexSrc   = loadFile(vertexPath);
    std::string fragmentSrc = loadFile(fragmentPath);

    if (vertexSrc.empty() || fragmentSrc.empty()) {
        std::cerr << "Shader sources empty. Check paths: "
                  << vertexPath << ", " << fragmentPath << std::endl;
    }

    m_rendererID = createProgram(vertexSrc, fragmentSrc);
}

Shader::~Shader() {
    glDeleteProgram(m_rendererID);
}

void Shader::bind() const {
    glUseProgram(m_rendererID);
}

void Shader::unbind() const {
    glUseProgram(0);
}

unsigned int Shader::compileShader(unsigned int type,
                                   const std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int success;
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);

    if (!success) {
        char log[2048];
        glGetShaderInfoLog(id, sizeof(log), nullptr, log);
        std::cerr << "Shader compile error:\n" << log << std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}

unsigned int Shader::createProgram(const std::string& vertexSrc,
                                   const std::string& fragmentSrc)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexSrc);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentSrc);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);

    int linked = 0;
    glGetProgramiv(program, GL_LINK_STATUS, &linked);
    if (!linked) {
        char log[2048];
        glGetProgramInfoLog(program, sizeof(log), nullptr, log);
        std::cerr << "Program link error:\n" << log << std::endl;
    }

    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

int Shader::getUniformLocation(const std::string& name)
{
    if (m_uniformLocationCache.count(name))
        return m_uniformLocationCache[name];

    int location = glGetUniformLocation(m_rendererID, name.c_str());
    if (location == -1) {
        // optional debug
        // std::cerr << "Warning: uniform '" << name << "' not found.\n";
    }
    m_uniformLocationCache[name] = location;
    return location;
}

void Shader::setUniform1i(const std::string& name, int v) {
    glUniform1i(getUniformLocation(name), v);
}

void Shader::setUniform1f(const std::string& name, float v) {
    glUniform1f(getUniformLocation(name), v);
}

void Shader::setUniform2f(const std::string& name, float x, float y) {
    glUniform2f(getUniformLocation(name), x, y);
}

void Shader::setUniform3f(const std::string& name, float x, float y, float z) {
    glUniform3f(getUniformLocation(name), x, y, z);
}

void Shader::setUniform4f(const std::string& name, float x, float y, float z, float w) {
    glUniform4f(getUniformLocation(name), x, y, z, w);
}

void Shader::setUniformMat4f(const std::string& name, const glm::mat4& m) {
    glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(m));
}

} // namespace pe
