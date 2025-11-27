#shader vertex
#version 330 core
layout(location = 0) in vec2 aPos;

uniform vec2  u_Pos;     // Bildschirmkoordinaten in NDC (-1..1)
uniform float u_Radius;  // Skalierung

out vec2 vLocal;         // unskalierte Kreis­koordinaten

void main() {
    vLocal = aPos;                       // für Fragment-Test
    vec2 pos = aPos * u_Radius + u_Pos;  // Skalieren + verschieben
    gl_Position = vec4(pos, 0.0, 1.0);
}

#shader fragment
#version 330 core
in  vec2 vLocal;
out vec4 FragColor;

uniform vec4 u_Color;   // RGBA

void main() {
    if (length(vLocal) > 1.0) discard;   // scharfer Rand
    FragColor = u_Color;
}
