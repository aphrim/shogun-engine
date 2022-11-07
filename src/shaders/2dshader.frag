#version 410 core

in vec2 FragPos;
in vec2 TexCord;
in vec3 Color;
out vec4 FragColor;

void main() {
    FragColor = vec4(Color, 0.5);
}
