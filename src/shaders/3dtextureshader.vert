#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCord;

out vec3 FragPos;
out vec2 TexCord;
out vec3 Normal;

uniform mat4 transform;
uniform mat4 projection;
uniform mat4 view;

void main() {
    gl_Position = projection * view * transform * vec4(aPos, 1.0);
    FragPos = vec3(transform * vec4(aPos, 1.0));
    TexCord = aTexCord;
    Normal = aNormal;
}
