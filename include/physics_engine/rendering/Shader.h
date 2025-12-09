#pragma once
#include <string>
#include <unordered_map>
#include <glm/glm.hpp>

namespace PhyEn {

    class Shader {
        public:
            // NEU: erwartet Pfade zu .vert und .frag
            Shader(const std::string& vertexPath,
                const std::string& fragmentPath);

            ~Shader();

            void bind() const;
            void unbind() const;

            void setUniform1i(const std::string& name, int v);
            void setUniform1f(const std::string& name, float v);
            void setUniform2f(const std::string& name, float x, float y);
            void setUniform3f(const std::string& name, float x, float y, float z);
            void setUniform4f(const std::string& name, float x, float y, float z, float w);
            void setUniformMat4f(const std::string& name, const glm::mat4& m);

        private:
            unsigned int m_rendererID;
            std::unordered_map<std::string, int> m_uniformLocationCache;

            static std::string loadFile(const std::string& path);

            unsigned int compileShader(unsigned int type, const std::string& source);
            unsigned int createProgram(const std::string& vertexSrc,
                                    const std::string& fragmentSrc);

            int getUniformLocation(const std::string& name);
    };

} // namespace pe
