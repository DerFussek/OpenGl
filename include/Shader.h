// Shader.h
#pragma once
#include <string>

struct ShaderProgramSource {
    std::string VertexSource;
    std::string FragmentSource;
};

class Shader {
public:
    Shader(const std::string& filepath, bool CreateOnStart);
    ~Shader();

    void Bind() const;
    void Unbind() const;

    void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3) const; // <- const
    int  GetUniformLocation(const std::string& name) const; // <- const

    void Create();

private:
    ShaderProgramSource ParseShader(const std::string& filepath) const;
    unsigned int CreateShader(const std::string& vs, const std::string& fs);
    unsigned int CompileShader(unsigned int type, const std::string& source);
    std::string  m_FilePath;
    unsigned int m_RendererID = 0;
};
