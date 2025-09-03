#pragma once
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

class ShaderProgramm {
    public:
        struct ShaderProgrammSource {
            std::string VertexSource;
            std::string FragmentSource;
        };

        ShaderProgrammSource Source;
        unsigned int ID;
        unsigned int PROGRAM;

    public:
        ShaderProgramm();
        ShaderProgramm(const std::string& rawFilePath);

        ShaderProgrammSource ParseShader(const std::string& filePath);
        unsigned int CompileShader(unsigned int type, const std::string& source);
        unsigned int CreateShader();
};