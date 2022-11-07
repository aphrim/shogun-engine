#version 410 core

layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexCord;

out vec3 FragPos;
out vec2 TexCord;
out vec3 Color;

uniform mat4 transform;
uniform vec3 color;

void main() {
    gl_Position = transform * vec4(aPos, 0.0, 1.0);
    FragPos = vec3(transform * vec4(aPos, 0.0, 1.0));
    Color = color;
}
