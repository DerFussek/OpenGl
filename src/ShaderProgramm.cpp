#include "ShaderProgramm.h"

ShaderProgramm::ShaderProgramm() {
    Source = {nullptr, nullptr};
}

ShaderProgramm::ShaderProgramm(const std::string& rawFilePath) {
    this->ParseShader(rawFilePath);
}

ShaderProgramm::ShaderProgrammSource ShaderProgramm::ParseShader(const std::string& filePath) {
    std::ifstream stream(filePath);
    
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
                } else if(line.find("fragment") != std::string::npos) {
                    type = ShaderType::FRAGMENT;
                }
           } else {
                ss[(int)type] << line << "\n";
           }
        }

    } catch (std::exception e) {
        std::cerr << "Catched Exception during File reading!\n";
        
        Source = {"-1", "-1"};
        return {"-1", "-1"};
    }

    Source = {ss[0].str(), ss[1].str()};
    return {ss[0].str(), ss[1].str()};
}

unsigned int ShaderProgramm::CompileShader(unsigned int type, const std::string& source) {
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();

    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    try {
        int res;
        glGetShaderiv(id, GL_COMPILE_STATUS, &res);

        if(res == GL_FALSE) {
            int len;
            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &len);
            char* msg = (char*)alloca(len * sizeof(char));

            glGetShaderInfoLog(id, len, &len, msg);
            glDeleteShader(id);

            throw msg;
            return 0;
        }
    } catch (const char* msg) {
        std::cerr << msg << std::endl;
    }
    
    this->ID = id;
    return id;
}

unsigned int ShaderProgramm::CreateShader() {
    unsigned int program = glCreateProgram();
    unsigned int vs = this->CompileShader(GL_VERTEX_SHADER, this->Source.VertexSource);
    unsigned int fs = this->CompileShader(GL_FRAGMENT_SHADER, this->Source.FragmentSource);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    this->PROGRAM = program;
    return program;
}