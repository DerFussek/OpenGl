#pragma once
#include <string>

struct ShaderProgramSource {
    std::string VertexSource;
    std::string FragmentSource;
};

class Shader {
    private:
        std::string m_Filepath;
        unsigned int m_ID;

    public:
        Shader(const std::string &filepath, bool CreateOnStart = true);
        ~Shader();

        void Bind() const;
        void Unbind() const;

        int GetUniformLocation(const std::string &name) const;
        void SetUniform4f(const std::string &name, float v0, float v1, float v2, float v3) const;


        void Create();

        inline unsigned int GetID() const { return m_ID; }
    
    private:
        ShaderProgramSource ParseShader(const std::string &filepath) const;
        unsigned int CreateShader(const std::string &vs, const std::string &fs);
        unsigned int CompileShader(unsigned int type, const std::string &source);
};

