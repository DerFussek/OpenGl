// TextRenderer.h
#pragma once

#include <string>
#include <map>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

struct Character
{
    GLuint TextureID;   // Glyph-Textur
    glm::ivec2 Size;    // Breite / Höhe in Pixeln
    glm::ivec2 Bearing; // Offset von Baseline zu Glyph
    GLuint Advance;     // Abstand zur nächsten Glyph in 1/64 Pixel
};

class TextRenderer
{
public:
    std::map<char, Character> Characters;
    GLuint VAO, VBO;
    GLuint shaderProgram;

    TextRenderer(GLuint shaderProgram, const std::string& fontPath, unsigned int fontSize);
    ~TextRenderer();

    void RenderText(const std::string& text,
                    float x,
                    float y,
                    float scale,
                    const glm::vec3& color,
                    const glm::mat4& projection);

private:
    void loadFont(const std::string& fontPath, unsigned int fontSize);
};
