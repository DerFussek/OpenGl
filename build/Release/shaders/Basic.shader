#shader vertex
#version 330 core

layout (location = 0) in vec2 aPos;

uniform vec2 u_Pos; // Position als Uniform

void main() {
    // aPos sind deine lokalen Koordinaten (zentrierter Rect),
    // u_Pos verschiebt alles im NDC-Raum
    gl_Position = vec4(aPos + u_Pos, 0.0, 1.0);
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

uniform vec4 u_Color;

void main() {
    color = u_Color;
}
