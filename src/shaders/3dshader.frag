#version 410 core

in vec3 FragPos;
in vec2 TexCord;
in vec3 Normal;
in vec3 Color;
out vec4 FragColor;

void main() {
    FragColor = vec4(Color,1.0);
}
