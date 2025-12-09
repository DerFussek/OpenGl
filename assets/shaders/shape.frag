#version 330 core
in vec2 v_TexCoord;

uniform vec4      u_Color;
uniform sampler2D u_Texture;
uniform int       u_UseTexture;

out vec4 FragColor;

void main()
{
    vec4 base = u_Color;

    if (u_UseTexture == 1)
        base *= texture(u_Texture, v_TexCoord);

    FragColor = base;
}
