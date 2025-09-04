#shader vertex
#version 330 core
layout (location = 0) in vec2 aPos;
void main() { gl_Position = vec4(aPos, 0.0, 1.0); }

#shader fragment
#version 330 core
<<<<<<< HEAD

layout(location = 0) out vec4 color;

uniform vec4 u_Color;

void main() {
    color = u_Color;
};
=======
out vec4 FragColor;
uniform vec4 u_Color;
void main() { FragColor = u_Color; }
>>>>>>> ef656056668d5939283e255393c4a60a6a29b819
